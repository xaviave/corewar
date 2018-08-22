/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_sti.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tduverge <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/16 19:39:03 by tduverge     #+#   ##    ##    #+#       */
/*   Updated: 2018/08/22 14:16:28 by tduverge    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/corewar.h"

static int	first_arg(t_champ *tmp, t_mem *mem, int *value, int *i)
{
	unsigned int		reg;

	if ((mem->memory[(tmp->pc + 1) % MEM_SIZE] & 0b11000000) >> 6 == 1)
	{
		reg = mem->memory[(tmp->pc + (*i)) % MEM_SIZE];
		if (!reg || reg > 16)
			return (0);
		value[0] = give_reg(tmp, reg);
		(*i)++;
		return (1);
	}
	return (0);
}

static int	second_arg(t_champ *tmp, t_mem *mem, int *value, int *i)
{
	unsigned int		reg;

	if ((mem->memory[(tmp->pc + 1) % MEM_SIZE] & 0b110000) >> 4 == 0)
		return (0);
	else if ((mem->memory[(tmp->pc + 1) % MEM_SIZE] & 0b110000) >> 4 == 1)
	{
		reg = mem->memory[(tmp->pc + (*i)) % MEM_SIZE];
		if (!reg || reg > 16)
			return (0);
		value[1] = give_reg(tmp, reg);
		(*i)++;
	}
	else
	{
		if ((mem->memory[(tmp->pc + 1) % MEM_SIZE] & 0b110000) >> 4 == 2)
			value[1] = recup_direct2(mem, tmp, *i);
		else
			value[1] = recup_indirect4x(mem, tmp, *i);
		if (value[1] & 0x8000)
			value[1] = value[1] | 0xffff0000;
		(*i) += 2;
	}
	return (1);
}

static int	third_arg(t_champ *tmp, t_mem *mem, int *value, int *i)
{
	unsigned int		reg;

	if ((mem->memory[(tmp->pc + 1) % MEM_SIZE] & 0b1100) >> 2 == 0)
		return (0);
	else if ((mem->memory[(tmp->pc + 1) % MEM_SIZE] & 0b1100) >> 2 == 3)
		return (0);
	else if ((mem->memory[(tmp->pc + 1) % MEM_SIZE] & 0b1100) >> 2 == 1)
	{
		reg = mem->memory[(tmp->pc + (*i)) % MEM_SIZE];
		if (!reg || reg > 16)
			return (0);
		value[2] = give_reg(tmp, reg);
		(*i)++;
	}
	else
	{
		value[2] = recup_direct2(mem, tmp, *i);
		if (value[2] & 0x8000)
			value[2] = value[2] | 0xffff0000;
		(*i) += 2;
	}
	return (1);
}

int			ft_sti(t_champ *tmp, t_champ **list, t_mem *mem, t_arg *args)
{
	int					i;
	int					value[3];
	int					add;

	args = (t_arg *)args;
	list = (t_champ **)list;
	i = 2;
	if (!first_arg(tmp, mem, value, &i) || !second_arg(tmp, mem, value, &i) ||
			!third_arg(tmp, mem, value, &i))
		return (ft_error2(mem->memory[(tmp->pc + 1) % MEM_SIZE], tmp, 3));
	add = (value[1] + value[2]) % IDX_MOD;
	add = (add + tmp->pc + MEM_SIZE) % MEM_SIZE;
	mem->memory[add] = (unsigned int)(value[0] & 0xFF000000) >> 24;
	mem->memory[(add + 1) % MEM_SIZE] =
		(unsigned int)(value[0] & 0xFF0000) >> 16;
	mem->memory[(add + 2) % MEM_SIZE] = (unsigned int)(value[0] & 0xFF00) >> 8;
	mem->memory[(add + 3) % MEM_SIZE] = (unsigned int)(value[0] & 0xFF);
	mem->map[add] = tmp->number;
	mem->map[(add + 1) % MEM_SIZE] = tmp->number;
	mem->map[(add + 2) % MEM_SIZE] = tmp->number;
	mem->map[(add + 3) % MEM_SIZE] = tmp->number;
	tmp->pc = mod_pc(tmp, i);
	return (-1);
}
