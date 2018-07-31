/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main_cw.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/19 14:58:22 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/23 19:11:19 by tduverge    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/corewar.h"

void	introduce(t_champ *list, t_arg *args)
{
	int			i;
	int			j;
	t_champ		*tmp;

	t_champ *test;
	tmp = list;
	ft_printf("Introducing contestants...\n");
	i = args->nb_players;
	while (i)
	{
		j = i - 1;
		tmp = list;
		while (j)
		{
			tmp = tmp->next;
			j--;
		}
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
			tmp->number, tmp->prog_size, tmp->name, tmp->comment);
		i--;
	}
}

int		main(int ac, char **av)
{
	t_champ	*list;
	t_arg	args;
	t_mem	mem;

	list = NULL;
	ft_bzero(args.champ_number, MAX_PLAYERS * sizeof(int));
	if (ac < 3 || (args.nb_players = check_cor(ac, av)) < 2 ||
			args.nb_players > MAX_PLAYERS || !parse_arg(ac, av, &args, &mem))
		return (ft_printf("./corewar [-graph] [-dump nbr_cycles] [[-n number] champion1.cor]\n"));
	init_champ(&list, &args);
	generate_memory(&list, &mem);
	if (mem.graph == 1)
		lets_graph(&list, &mem, &args);
	else
	{
		introduce(list, &args);
		if (mem.dump == -1)
			lets_go(&list, &mem, &args);
		else
			lets_dump(&list, &mem, &args);
	}
	if (mem.graph == -1 && (mem.dump == -1 || mem.c != mem.dump))
		ft_printf("Contestant %d, \"%s\", has won !\n",
			mem.last_live, args.name[mem.last_live - 1]);
}
