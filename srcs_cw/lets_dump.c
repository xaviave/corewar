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
	int		tmp;
	int		very_less;

	mem->c = 0;
	very_less = 0;
	mem->c_todie = CYCLE_TO_DIE;
	tmp = mem->c_todie;
	while (mem->c <= args->dump && *list)
	{
		if (mem->c_todie ==  0)
		{
			check_live(list);
			if (mem->call_live >= NBR_LIVE || very_less == MAX_CHECKS - 1)
			{
				mem->c_todie = tmp - CYCLE_DELTA;
				tmp = mem->c_todie;
				very_less = 0;
			}
			else
			{
				very_less++;
				mem->c_todie = tmp;
			}
			mem->call_live = 0;
			if (mem->c_todie < 0)
				kill_them_all(list);
		}
		check_cycle(list, mem, mem->c, args);
		mem->c_todie--;
		mem->c++;
	}
	if (*list)
	{
		print_dump(mem, *list);
		kill_them_all(list);
	}
	else
		args->dump = -1;
	return (0);
}
