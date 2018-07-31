/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_ldi.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tduverge <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/16 21:51:14 by tduverge     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/24 21:04:35 by tduverge    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/corewar.h"

int		ft_ldi(t_champ *tmp, t_champ **list, t_mem *mem, t_arg *args)
{
	unsigned int		i;
	int					value[3];
	unsigned int		reg;

	args = (t_arg *)args;
	i = 2;
	if ((mem->memory[(tmp->pc + 1) % MEM_SIZE] & 0b11000000) >> 6 == 1)
	{
		reg = mem->memory[(tmp->pc + i) % MEM_SIZE];
		if (!reg || reg > 16)
			return (ft_error2(mem->memory[(tmp->pc + 1) % MEM_SIZE], tmp, 3));
		value[0] = give_reg(tmp, reg);
		i++;
	}
	else if ((mem->memory[(tmp->pc + 1) % MEM_SIZE] & 0b11000000) >> 6 == 2)
	{
		value[0] = recup_direct2(mem, tmp, i);
		i += 2;
	}
	else if ((mem->memory[(tmp->pc + 1) % MEM_SIZE] & 0b11000000) >> 6 == 3)
	{
		value[0] = recup_indirect2x(mem, tmp, i);
		i += 2;
	}
	else
		return (ft_error2(mem->memory[(tmp->pc + 1) % MEM_SIZE], tmp, 3));
	if ((mem->memory[(tmp->pc + 1) % MEM_SIZE] & 0b110000) >> 4 == 1)
	{
		reg = mem->memory[(tmp->pc + i) % MEM_SIZE];
		if (!reg || reg > 16)
			return (ft_error2(mem->memory[(tmp->pc + 1) % MEM_SIZE], tmp, 3));
		value[1] = give_reg(tmp, reg);
		i++;
	}
	else if ((mem->memory[(tmp->pc + 1) % MEM_SIZE] & 0b110000) >> 4 == 2)
	{
		value[1] = recup_direct2(mem, tmp, i);;
		i += 2;
	}
	else
		return (ft_error2(mem->memory[(tmp->pc + 1) % MEM_SIZE], tmp, 3));
	reg = mem->memory[(tmp->pc + i) % MEM_SIZE];
	if (value[0] & 0x8000)
		value[0] = value[0] | 0xffff0000;
	if (value[1] & 0x8000)
		value[1] = value[1] | 0xffff0000;
	if ((mem->memory[(tmp->pc + 1) % MEM_SIZE] & 0b1100) >> 2 == 1 && reg &&
			reg < 17 && !(mem->memory[(tmp->pc + 1) % MEM_SIZE] & 0b11))
	{
		value[2] = recup_direct4(mem, tmp, (value[0] + value[1]) % IDX_MOD);
		write_reg(tmp, mem->memory[(tmp->pc + i) % MEM_SIZE], value[2]);
		tmp->pc = mod_pc(tmp, *list, mem, i + 1);
		return (-1);
	}
	else
		return (ft_error2(mem->memory[(tmp->pc + 1) % MEM_SIZE], tmp, 3));
}
