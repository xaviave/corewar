/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lets_go.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tduverge <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/09 16:14:43 by tduverge     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/24 21:12:03 by tduverge    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/corewar.h"

int		lets_go(t_champ **list, t_mem *mem, t_arg *args)
{
	int		very_less;

	mem->c = 0;
	very_less = 0;
	mem->c_todie = CYCLE_TO_DIE;
	mem->c_before_check = mem->c_todie;
	while (*list)
		one_cycle(list, mem, args, &very_less);
	return (0);
}
