/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lets_dump.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tduverge <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/09 17:04:49 by tduverge     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/23 17:18:14 by tduverge    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/corewar.h"

int		lets_dump(t_champ **list, t_mem *mem, t_arg *args)
{
	int		very_less;

	mem->c = 0;
	very_less = 0;
	mem->c_todie = CYCLE_TO_DIE;
	mem->c_before_check = mem->c_todie;
	while (mem->c < args->dump && *list)
		one_cycle(list, mem, args, &very_less);
	if (*list)
	{
		print_dump(mem);
		kill_them_all(list);
	}
	else
		args->dump = -1;
	return (0);
}
