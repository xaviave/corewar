/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_st.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tduverge <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/16 17:10:29 by tduverge     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/19 18:28:13 by tduverge    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/corewar.h"

int			ft_st(t_champ *tmp, t_champ **list, t_mem *mem, t_arg *args)
{
	int		value;
	int		add;

	args = (t_arg *)args;
	value = give_reg(tmp, mem->memory[(tmp->pc + 2) % MEM_SIZE]);
	if (mem->memory[(tmp->pc + 1) % MEM_SIZE] == 80 &&
			mem->memory[(tmp->pc + 3) % MEM_SIZE] <= 16 &&
				mem->memory[(tmp->pc + 3) % MEM_SIZE])
	{
		write_reg(tmp, mem->memory[(tmp->pc + 3) % MEM_SIZE], value);
		tmp->pc = mod_pc(tmp, *list, mem, 4);
	}
	else if (mem->memory[(tmp->pc + 1) % MEM_SIZE] == 112)
	{
		add = recup_direct2(mem, tmp, 3);
		if (add & 0x8000)
			add = add % IDX_MOD - 512;
		else
			add = add % IDX_MOD;
		mem->memory[(tmp->pc + add + MEM_SIZE) % MEM_SIZE] = (unsigned int)(value & 0xFF000000) >> 24;
		mem->memory[(tmp->pc + add + 1 + MEM_SIZE) % MEM_SIZE] = (unsigned int)(value & 0xFF0000) >> 16;
		mem->memory[(tmp->pc + add + 2 + MEM_SIZE) % MEM_SIZE] = (unsigned int)(value & 0xFF00) >> 8;
		mem->memory[(tmp->pc + add + 3 + MEM_SIZE) % MEM_SIZE] = (unsigned int)(value & 0xFF);
		mem->map[(tmp->pc + add + MEM_SIZE) % MEM_SIZE] = tmp->number;
		mem->map[(tmp->pc + add + 1 + MEM_SIZE) % MEM_SIZE] = tmp->number;
		mem->map[(tmp->pc + add + 2 + MEM_SIZE) % MEM_SIZE] = tmp->number;
		mem->map[(tmp->pc + add + 3 + MEM_SIZE) % MEM_SIZE] = tmp->number;
		tmp->pc = mod_pc(tmp, *list, mem, 5);
	}
	else
		ft_error(mem->memory[(tmp->pc + 1) % MEM_SIZE], tmp, -1);
	return (-1);
}