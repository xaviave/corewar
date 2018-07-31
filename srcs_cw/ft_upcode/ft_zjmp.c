/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_zjmp.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tduverge <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/16 19:14:48 by tduverge     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/24 21:10:57 by tduverge    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/corewar.h"

int		ft_zjmp(t_champ *tmp, t_champ **list, t_mem *mem, t_arg *args)
{
	int		value;

	args = (t_arg *)args;
	list = (t_champ **)list;
	value = recup_direct2(mem, tmp, 1);
	if (value & 0x8000)
		value = value | 0xffff0000;
	value = value % IDX_MOD;
	if (tmp->carry == 0)
	{
		tmp->pc = mod_pc(tmp, 3);
		return (-1);
	}
	tmp->pc = mod_pc(tmp, value);
	return (-1);
}
