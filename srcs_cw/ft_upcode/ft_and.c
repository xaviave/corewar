/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_and.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tduverge <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/16 18:37:15 by tduverge     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/24 21:03:13 by tduverge    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/corewar.h"

int		ft_and(t_champ *tmp, t_champ **list, t_mem *mem, t_arg *args)
{
	unsigned int		i;
	unsigned int		value[2];
	unsigned int		reg;

	args = (t_arg *)args;
	i = 2;
	if ((mem->memory[(tmp->pc + 1) % MEM_SIZE] & 0b11000000) >> 6 == 1)
	{
		reg = mem->memory[(tmp->pc + i) % MEM_SIZE];
		if (!reg || reg > 16)
			return (ft_error(mem->memory[(tmp->pc + 1) % MEM_SIZE], tmp, 0, 3));
		value[0] = give_reg(tmp, mem->memory[(tmp->pc + i) % MEM_SIZE]);
		i++;
	}
	else if ((mem->memory[(tmp->pc + 1) % MEM_SIZE] & 0b11000000) >> 6 == 2)
	{
		value[0] = recup_direct4(mem, tmp, i);;
		i += 4;
	}
	else if ((mem->memory[(tmp->pc + 1) % MEM_SIZE] & 0b11000000) >> 6 == 3)
	{
		value[0] = recup_indirect4x(mem, tmp, i);
		i += 2;
	}
	else
		return (ft_error(mem->memory[(tmp->pc + 1) % MEM_SIZE], tmp, 0, 3));
	if ((mem->memory[(tmp->pc + 1) % MEM_SIZE] & 0b110000) >> 4 == 1)
	{
		reg = mem->memory[(tmp->pc + i) % MEM_SIZE];
		if (!reg || reg > 16)
			return (ft_error(mem->memory[(tmp->pc + 1) % MEM_SIZE], tmp, 0, 3));
		value[1] = give_reg(tmp, reg);
		i++;
	}
	else if ((mem->memory[(tmp->pc + 1) % MEM_SIZE] & 0b110000) >> 4 == 2)
	{
		value[1] = recup_direct4(mem, tmp, i);;
		i += 4;
	}
	else if ((mem->memory[(tmp->pc + 1) % MEM_SIZE] & 0b110000) >> 4 == 3)
	{
		value[1] = recup_indirect4x(mem, tmp, i);
		i += 2;
	}
	else
		return (ft_error(mem->memory[(tmp->pc + 1) % MEM_SIZE], tmp, 0, 3));
	reg = mem->memory[(tmp->pc + i) % MEM_SIZE];
	if ((mem->memory[(tmp->pc + 1) % MEM_SIZE] & 0b1100) >> 2 == 1 && reg &&
			reg < 17 && !(mem->memory[(tmp->pc + 1) % MEM_SIZE] & 0b11))
	{
		write_reg(tmp, reg, value[0] & value[1]);
		tmp->pc = mod_pc(tmp, *list, mem, i + 1);
		return ((value[0] & value[1]) == 0 ? 1 : 0);
	}
	else
		return (ft_error(mem->memory[(tmp->pc + 1) % MEM_SIZE], tmp, 0, 3));
}
