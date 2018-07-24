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
	int		less;
	int		very_less;

	mem->c = 0;
	very_less = 0;
	mem->c_todie = CYCLE_TO_DIE;
	tmp = mem->c_todie;
	while (mem->c < mem->dump)
	{
		if (mem->c_todie ==  0)
		{
			if (!(less = check_live(list)))
				break;
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
				break;
		}
		check_cycle(list, mem, mem->c, args);
		mem->c_todie--;
		mem->c++;
	}
	print_dump(mem, *list);
	return (0);
}
