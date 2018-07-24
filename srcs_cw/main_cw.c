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
