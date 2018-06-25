/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main_cw.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/19 14:58:22 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/25 17:44:25 by tduverge    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/corewar.h"

int		parse_arg(int ac, char **av, t_arg *args)
{
	int		i;
	int		champ;

	i = 1;
	if (!ft_strcmp(av[1], "-dump"))
	{
		if (i + 1 == ac || !ft_strisdigit(av[i + 1]))
			return (0);
		args->dump = ft_atoi(av[i + 1]);
		i += 2;
	}
	champ = 0;
	while (i < ac)
	{
		if (!ft_strcmp(av[i], "-n"))
		{
			if (i + 2 >= ac || !ft_strisdigit(av[i + 1]))
				return (0);
			args->champ_number[champ] = ft_atoi(av[i + 1]);
			i += 2;
		}
		else
			args->champ_number[champ] = -1;
		args->champ_path[champ] = av[i];
		champ++;
		i++;
	}
	return (1);
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
	int	cor;
	t_champ	*list;
	t_arg	args;

	list = NULL;
	if (ac < 3 || !parse_arg(ac, av, &args) ||
			((cor = check_cor(ac, av)) < 2 && cor > 4))
		return (ft_printf("ERROR ARGS\n"));
	args.cor = cor;
	init_champ(&list, &args);
//	generate_memory(&list);
}
