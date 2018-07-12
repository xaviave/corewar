/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main_cw.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/19 14:58:22 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/09 17:06:35 by tduverge    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/corewar.h"

int		parse_player(int ac, char **av, t_arg *args, int i)
{
	int		champ;
	char	*temp[MAX_PLAYERS];
	int		j;

	champ = 0;
	ft_bzero(temp, MAX_PLAYERS * sizeof(char*));
	while (i < ac)
	{
		if (!ft_strcmp(av[i], "-n"))
		{
			if (i + 2 >= ac || !ft_strisdigit(av[i + 1])
					|| ft_atoi(av[i + 1]) > args->nb_players
					|| args->champ_number[ft_atoi(av[i + 1]) - 1] == 1)
				return (0);
			args->champ_number[ft_atoi(av[i + 1]) - 1] = 1;
			args->champ_path[ft_atoi(av[i + 1]) - 1] = av[i + 2];
			i += 2;
		}
		else
		{
			temp[champ] = av[i];
			champ++;
		}
		i++;
	}
	j = 0;
	while (j < champ)
	{
		i = 0;
		while (args->champ_path[i])
			i++;
		args->champ_path[i] = temp[j];
		j++;;
	}
	return (1);
}

int		parse_arg(int ac, char **av, t_arg *args, t_mem *aff)
{
	int		i;

	i = 1;
	if (!ft_strcmp(av[1], "-dump"))
	{
		if (i + 1 == ac || !ft_strisdigit(av[i + 1]))
			return (0);
		aff->dump = ft_atoi(av[i + 1]);
		i += 2;
	}
	else
		aff->dump = -1;
	ft_bzero(args->champ_path, MAX_PLAYERS * sizeof(char*));
	ft_bzero(args->champ_number, MAX_PLAYERS * sizeof(int));
	return (parse_player(ac, av, args, i));
}

int		check_cor(int ac, char **av)
{
	int	i;
	int	j;
	int	cor;

	cor = 0;
	i = 0;
	while (++i < ac)
	{
		j = ft_strlen(av[i]) - 1;
		if (j >= 3 && av[i][j] == 'r' && av[i][j - 1] == 'o'
				&& av[i][j - 2] == 'c' && av[i][j - 3]== '.')
			cor++;
	}
	return (cor);
}

int		main(int ac, char **av)
{
	t_champ	*list;
	t_arg	args;
	t_mem	aff;

	list = NULL;
	ft_bzero(args.champ_number, MAX_PLAYERS * sizeof(int));
	if (ac < 3 || (args.nb_players = check_cor(ac, av)) < 2 ||
			args.nb_players > MAX_PLAYERS || !parse_arg(ac, av, &args, &aff))
		return (ft_printf("./corewar [-dump nbr_cycles] [[-n number] champion1.cor]\n"));
	init_champ(&list, &args);
	generate_memory(&list, &aff);
	aff.dump == -1 ? lets_go(&list, &aff, &args) : lets_dump(&list, &aff, &args);
}
