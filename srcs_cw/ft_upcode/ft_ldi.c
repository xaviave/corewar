/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_ldi.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tduverge <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/16 21:51:14 by tduverge     #+#   ##    ##    #+#       */
/*   Updated: 2018/08/22 14:11:43 by tduverge    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/corewar.h"

static int	first_arg(t_champ *tmp, t_mem *mem, int *value, int *i)
{
	unsigned int		reg;

	if ((mem->memory[(tmp->pc + 1) % MEM_SIZE] & 0b11000000) >> 6 == 0)
		return (0);
	else if ((mem->memory[(tmp->pc + 1) % MEM_SIZE] & 0b11000000) >> 6 == 1)
	{
		reg = mem->memory[(tmp->pc + (*i)) % MEM_SIZE];
		if (!reg || reg > 16)
			return (0);
		value[0] = give_reg(tmp, reg);
		(*i)++;
	}
	else
	{
		if ((mem->memory[(tmp->pc + 1) % MEM_SIZE] & 0b11000000) >> 6 == 2)
			value[0] = recup_direct2(mem, tmp, *i);
		else
			value[0] = recup_indirect2x(mem, tmp, *i);
		if (value[0] & 0x8000)
			value[0] = value[0] | 0xffff0000;
		(*i) += 2;
	}
	return (1);
}

static int	second_arg(t_champ *tmp, t_mem *mem, int *value, int *i)
{
	unsigned int		reg;

	if ((mem->memory[(tmp->pc + 1) % MEM_SIZE] & 0b110000) >> 4 == 0)
		return (0);
	else if ((mem->memory[(tmp->pc + 1) % MEM_SIZE] & 0b110000) >> 4 == 3)
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
		value[1] = recup_direct2(mem, tmp, *i);
		if (value[1] & 0x8000)
			value[1] = value[1] | 0xffff0000;
		(*i) += 2;
	}
	return (1);
}

int			ft_ldi(t_champ *tmp, t_champ **list, t_mem *mem, t_arg *args)
{
	int					i;
	int					value[3];
	unsigned int		reg;

	args = (t_arg *)args;
	list = (t_champ **)list;
	i = 2;
	if (!first_arg(tmp, mem, value, &i))
		return (ft_error2(mem->memory[(tmp->pc + 1) % MEM_SIZE], tmp, 3));
	if (!second_arg(tmp, mem, value, &i))
		return (ft_error2(mem->memory[(tmp->pc + 1) % MEM_SIZE], tmp, 3));
	reg = mem->memory[(tmp->pc + i) % MEM_SIZE];
	if ((mem->memory[(tmp->pc + 1) % MEM_SIZE] & 0b1100) >> 2 == 1 && reg &&
			reg < 17)
	{
		value[2] = recup_direct4(mem, tmp, (value[0] + value[1]) % IDX_MOD);
		write_reg(tmp, mem->memory[(tmp->pc + i) % MEM_SIZE], value[2]);
		tmp->pc = mod_pc(tmp, i + 1);
		return (-1);
	}
	else
		return (ft_error2(mem->memory[(tmp->pc + 1) % MEM_SIZE], tmp, 3));
}
