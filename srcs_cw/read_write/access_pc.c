/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   access_pc.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tduverge <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/14 14:42:54 by tduverge     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/16 23:50:16 by tduverge    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/corewar.h"

int		mod_pc(t_champ *tmp, t_champ *list, t_mem *mem, int nu)
{
	return ((tmp->pc + nu) % MEM_SIZE);
	list = (t_champ *)list;
	mem = (t_mem *)mem;
//	print_mem(mem, list);
}
