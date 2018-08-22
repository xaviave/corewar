/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   all_init_is_love.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tduverge <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/22 14:18:16 by tduverge     #+#   ##    ##    #+#       */
/*   Updated: 2018/08/22 14:58:30 by tduverge    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/corewar.h"

static int		put_usage(t_arg *args, int error, char **av)
{
	ft_printf("Usage: ./corewar [-aff] [-graph] [-dump nbr_cycles] ");
	ft_printf("[[-n number] champion1.cor]\n");
	if (error == 1 || error == 2)
		ft_printf("\t>>> We need at least one champion to make a fight...");
	else if (error == 3)
		ft_printf("\t>>> We are not wild, not more than %d in a fight.",
				MAX_PLAYERS);
	else if (error == 4)
		ft_printf("\t>>> Stupid, \"-dump\" has to be followed by a number.");
	else if (error == 5)
		ft_printf("\t>>> Don't use illegal option, terrorist !");
	else if (error == 6)
		ft_printf("\t>>> \"-n\" has to be followed by%s",
		" a valid number AND a champion");
	else if (error >= 7)
		ft_printf("\t>>> I don't think \"%s\" is a valid file.", av[error - 7]);
	else if (error < 0)
		ft_printf("\t>>> I don't think \"%s\" is a valid file.",
				args->champ_path[-(error + 1)]);
	ft_printf("\n");
	ft_printf("For more information you can use : \"./corewar -help\"\n");
	return (1);
}

static int		global_check(int ac, char **av)
{
	int		i;

	i = 1;
	while (i < ac && av[i][0] == '-' && av[i][1] != 'n')
	{
		if (!ft_strcmp(av[i], "-dump"))
			i++;
		i++;
	}
	while (i < ac)
	{
		if (!ft_strcmp(av[i], "-n") && i + 2 < ac && check_cor_file(av[i + 2]))
			i += 3;
		else if (check_cor_file(av[i]))
			i++;
		else
			return (i + 7);
	}
	return (0);
}

int				all_init_is_love(t_champ **list, t_arg *args, int ac, char **av)
{
	int		error;

	if (ac < 2)
		return (put_usage(args, 1, av));
	else if ((error = global_check(ac, av)))
		return (put_usage(args, error, av));
	else if ((args->nb_players = check_cor_nb(ac, av)) < 1)
		return (put_usage(args, 2, av));
	else if (args->nb_players > MAX_PLAYERS)
		return (put_usage(args, 3, av));
	else if ((error = parse_arg(ac, av, args)))
		return (put_usage(args, error, av));
	else if ((error = init_champ(list, args)))
		return (put_usage(args, error, av));
	return (0);
}
