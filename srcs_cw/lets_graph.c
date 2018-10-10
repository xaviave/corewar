/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lets_graph.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tduverge <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/22 14:20:28 by tduverge     #+#   ##    ##    #+#       */
/*   Updated: 2018/08/22 14:20:29 by tduverge    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/corewar.h"

int		lets_graph(t_champ **list, t_mem *mem, t_arg *args)
{
	int		very_less;
	int		stop;

	mem->c = 0;
	very_less = 0;
	mem->c_todie = CYCLE_TO_DIE;
	mem->c_before_check = mem->c_todie;
	while (args->dump != -1 && mem->c < args->dump && *list)
		one_cycle(list, mem, args, &very_less);
	init_window(mem, *list, args, &stop);
	while (*list)
	{
		one_cycle(list, mem, args, &very_less);
		stop = print_mem(mem, *list, args, stop);
	}
	print_mem(mem, *list, args, 0);
	nodelay(stdscr, 0);
	getch();
	endwin();
	return (0);
}
