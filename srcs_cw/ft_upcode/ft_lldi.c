/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_lldi.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tduverge <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/16 21:52:03 by tduverge     #+#   ##    ##    #+#       */
/*   Updated: 2018/08/22 14:12:29 by tduverge    ###    #+. /#+    ###.fr     */
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
	}
	else if ((mem->memory[(tmp->pc + 1) % MEM_SIZE] & 0b11000000) >> 6 == 2)
	{
		value[0] = recup_direct2(mem, tmp, (*i));
		(*i) += 2;
	}
	else if ((mem->memory[(tmp->pc + 1) % MEM_SIZE] & 0b11000000) >> 6 == 3)
	{
		value[0] = recup_indirect2(mem, tmp, (*i));
		(*i) += 2;
	}
	else
		return (0);
	return (1);
}

static int	second_arg(t_champ *tmp, t_mem *mem, int *value, int *i)
{
	unsigned int		reg;

	if ((mem->memory[(tmp->pc + 1) % MEM_SIZE] & 0b110000) >> 4 == 1)
	{
		reg = mem->memory[(tmp->pc + (*i)) % MEM_SIZE];
		if (!reg || reg > 16)
			return (0);
		value[1] = give_reg(tmp, reg);
		(*i)++;
	}
	else if ((mem->memory[(tmp->pc + 1) % MEM_SIZE] & 0b110000) >> 4 == 2)
	{
		value[1] = recup_direct2(mem, tmp, *i);
		(*i) += 2;
	}
	else
		return (0);
	return (1);
}

int			ft_lldi(t_champ *tmp, t_champ **list, t_mem *mem, t_arg *args)
{
	int					i;
	int					value[3];
	unsigned int		reg;

	list = (t_champ **)list;
	args = (t_arg *)args;
	i = 2;
	if (!first_arg(tmp, mem, value, &i))
		return (ft_error2(mem->memory[(tmp->pc + 1) % MEM_SIZE], tmp, 3));
	if (!second_arg(tmp, mem, value, &i))
		return (ft_error2(mem->memory[(tmp->pc + 1) % MEM_SIZE], tmp, 3));
	reg = mem->memory[(tmp->pc + i) % MEM_SIZE];
	if ((mem->memory[(tmp->pc + 1) % MEM_SIZE] & 0b1100) >> 2 == 1 && reg &&
			reg < 17)
	{
		value[2] = recup_direct4(mem, tmp, value[0] + value[1]);
		write_reg(tmp, mem->memory[(tmp->pc + i) % MEM_SIZE], value[2]);
		tmp->pc = mod_pc(tmp, i + 1);
		return (value[2] == 0 ? 1 : 0);
	}
	else
		return (ft_error2(mem->memory[(tmp->pc + 1) % MEM_SIZE], tmp, 3));
}
