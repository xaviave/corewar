/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_lld.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tduverge <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/16 21:52:27 by tduverge     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/16 23:30:09 by tduverge    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/corewar.h"

int		ft_lld(t_champ *tmp, t_champ *list, t_mem *mem, t_arg *args)
{
	int		value;
	int		reg;

	args = (t_arg *)args;
	if (mem->memory[(tmp->pc + 1) % MEM_SIZE] == 144)
	{
		value = recup_direct4(mem, tmp, 2);
		reg = (int)mem->memory[(tmp->pc + 6) % MEM_SIZE];
		tmp->pc = mod_pc(tmp, list, mem, 7);
		//tmp->pc = (7 + tmp->pc) % MEM_SIZE;
		if (reg <= 0 || reg >= 16)
			return (0);
		write_reg(tmp, reg, value);
		return (value == 0 ? 1 : 0);
	}
	else if (mem->memory[(tmp->pc + 1) % MEM_SIZE] == 208)
	{
		value = recup_indirect4(mem, tmp, 2);
		reg = (int)mem->memory[(tmp->pc + 4) % MEM_SIZE];
		tmp->pc = mod_pc(tmp, list, mem, 5);
		//tmp->pc = (5 + tmp->pc) % MEM_SIZE;
		if (reg <= 0 || reg >= 16)
			return (0);
		write_reg(tmp, reg, value);
		return (value == 0 ? 1 : 0);
	}
	tmp->pc = mod_pc(tmp, list, mem, 4);
	//tmp->pc = (4 + tmp->pc) % MEM_SIZE;
	return (0);
}
