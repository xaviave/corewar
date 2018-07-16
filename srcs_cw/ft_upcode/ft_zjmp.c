/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_zjmp.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tduverge <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/16 19:14:48 by tduverge     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/16 20:25:59 by tduverge    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/corewar.h"

int		ft_zjmp(t_champ *tmp, t_champ *list, t_mem *mem, t_arg *args)
{
	int		value;

	value = recup_direct2(mem, tmp, 1);
	args = (t_arg *)args;
	if (tmp->carry == 0 || value == 0)
	{
		tmp->pc = mod_pc(tmp, list, mem, 4);
		return (-1);
	}
	tmp->pc = mod_pc(tmp, list, mem, value);
	return (-1);
}
