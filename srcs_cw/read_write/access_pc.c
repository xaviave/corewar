/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   access_pc.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tduverge <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/14 14:42:54 by tduverge     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/19 18:38:41 by tduverge    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/corewar.h"

int		mod_pc(t_champ *tmp, t_champ *list, t_mem *mem, int nu)
{
	int pc;

	pc = (tmp->pc + nu + MEM_SIZE) % MEM_SIZE;
	return (pc);
	print_mem(mem, list);
}
