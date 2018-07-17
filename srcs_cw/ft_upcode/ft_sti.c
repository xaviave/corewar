/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_sti.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tduverge <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/16 19:39:03 by tduverge     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/17 21:03:35 by tduverge    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/corewar.h"

int		ft_sti(t_champ *tmp, t_champ *list, t_mem *mem, t_arg *args)
{
	unsigned int		i;
	unsigned int		value[3];
	int					add;
	unsigned int		reg;

	args = (t_arg *)args;
	i = 2;
	if ((mem->memory[(tmp->pc + 1) % MEM_SIZE] & 0b11000000) >> 6 == 1)
	{
		reg = mem->memory[(tmp->pc + i) % MEM_SIZE];
		if (!reg || reg > 16)
			return (ft_error(mem->memory[(tmp->pc + 1) % MEM_SIZE], tmp, -1));
		value[0] = give_reg(tmp, reg);
		i++;
	}
	else
	{
		tmp->pc = mod_pc(tmp, list, mem, 7);
		return (-1);
	}
	if ((mem->memory[(tmp->pc + 1) % MEM_SIZE] & 0b110000) >> 4 == 1)
	{
		reg = mem->memory[(tmp->pc + i) % MEM_SIZE];
		if (!reg || reg > 16)
			return (ft_error(mem->memory[(tmp->pc + 1) % MEM_SIZE], tmp, -1));
		value[1] = give_reg(tmp, reg);
		i++;
	}
	else if ((mem->memory[(tmp->pc + 1) % MEM_SIZE] & 0b110000) >> 4 == 2)
	{
		value[1] = recup_direct2(mem, tmp, i);;
		i += 2;
	}
	else if ((mem->memory[(tmp->pc + 1) % MEM_SIZE] & 0b110000) >> 4 == 3)
	{
		value[1] = recup_indirect2x(mem, tmp, i);
		i += 2;
	}
	else
	{
		tmp->pc = mod_pc(tmp, list, mem, 7);
		return (-1);
	}
	if ((mem->memory[(tmp->pc + 1) % MEM_SIZE] & 0b110000) >> 4 == 1)
	{
		reg = mem->memory[(tmp->pc + i) % MEM_SIZE];
		if (!reg || reg > 16)
			return (ft_error(mem->memory[(tmp->pc + 1) % MEM_SIZE], tmp, -1));
		value[2] = give_reg(tmp, reg);
		i++;
	}
	else if ((mem->memory[(tmp->pc + 1) % MEM_SIZE] & 0b110000) >> 4 == 2)
	{
		value[2] = recup_direct2(mem, tmp, i);;
		i += 2;
	}
	else
		return (ft_error(mem->memory[(tmp->pc + 1) % MEM_SIZE], tmp, -1));
	if (value[1] & 0x8000)
		value[1] = value[1] % IDX_MOD - 512;
	else
		value[1] = value[1] % IDX_MOD;
	if (value[2] & 0x8000)
		value[2] = value[2] % IDX_MOD - 512;
	else
		value[2] = value[2] % IDX_MOD;
	add = value[1] + value[2];
	if (add & 0x8000)
		add = add % IDX_MOD - 512;
	else
		add= add % IDX_MOD;
	mem->memory[(tmp->pc + add) % MEM_SIZE] = (unsigned int)(value[0] & 0xFF000000) >> 24;
	mem->memory[(tmp->pc + add + 1) % MEM_SIZE] = (unsigned int)(value[0] & 0xFF0000) >> 16;
	mem->memory[(tmp->pc + add + 2) % MEM_SIZE] = (unsigned int)(value[0] & 0xFF00) >> 8;
	mem->memory[(tmp->pc + add + 3) % MEM_SIZE] = (unsigned int)(value[0] & 0xFF);
	tmp->pc = mod_pc(tmp, list, mem, i);
	return (-1);
}
