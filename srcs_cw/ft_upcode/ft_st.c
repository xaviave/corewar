/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_st.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tduverge <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/16 17:10:29 by tduverge     #+#   ##    ##    #+#       */
/*   Updated: 2018/08/22 14:13:56 by tduverge    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/corewar.h"

static int		first_case(t_champ *tmp, t_mem *mem, unsigned int reg_src)
{
	unsigned int	reg_dst;
	int				value;

	reg_dst = mem->memory[(tmp->pc + 3) % MEM_SIZE];
	if (!reg_src || !reg_dst || reg_src > 16 || reg_dst > 16)
		return (0);
	value = give_reg(tmp, reg_src);
	write_reg(tmp, reg_dst, value);
	tmp->pc = mod_pc(tmp, 4);
	return (1);
}

static int		second_case(t_champ *tmp, t_mem *mem, unsigned int reg_src)
{
	int				add;
	int				value;

	if (!reg_src || reg_src > 16)
		return (0);
	add = recup_direct2(mem, tmp, 3);
	if (add & 0x8000)
		add = add | 0xffff0000;
	add = add % IDX_MOD;
	value = give_reg(tmp, reg_src);
	mem->memory[(tmp->pc + add + MEM_SIZE) % MEM_SIZE] =
		(unsigned int)(value & 0xFF000000) >> 24;
	mem->memory[(tmp->pc + add + 1 + MEM_SIZE) % MEM_SIZE] =
		(unsigned int)(value & 0xFF0000) >> 16;
	mem->memory[(tmp->pc + add + 2 + MEM_SIZE) % MEM_SIZE] =
		(unsigned int)(value & 0xFF00) >> 8;
	mem->memory[(tmp->pc + add + 3 + MEM_SIZE) % MEM_SIZE] =
		(unsigned int)(value & 0xFF);
	mem->map[(tmp->pc + add + MEM_SIZE) % MEM_SIZE] = tmp->number;
	mem->map[(tmp->pc + add + 1 + MEM_SIZE) % MEM_SIZE] = tmp->number;
	mem->map[(tmp->pc + add + 2 + MEM_SIZE) % MEM_SIZE] = tmp->number;
	mem->map[(tmp->pc + add + 3 + MEM_SIZE) % MEM_SIZE] = tmp->number;
	tmp->pc = mod_pc(tmp, 5);
	return (1);
}

int				ft_st(t_champ *tmp, t_champ **list, t_mem *mem, t_arg *args)
{
	list = (t_champ **)list;
	args = (t_arg *)args;
	if ((mem->memory[(tmp->pc + 1) % MEM_SIZE] & 0xf0) == 80
		&& first_case(tmp, mem, mem->memory[(tmp->pc + 2) % MEM_SIZE]))
		return (-1);
	else if ((mem->memory[(tmp->pc + 1) % MEM_SIZE] & 0xf0) == 112
		&& second_case(tmp, mem, mem->memory[(tmp->pc + 2) % MEM_SIZE]))
		return (-1);
	else
		return (ft_error4(mem->memory[(tmp->pc + 1) % MEM_SIZE], tmp, 2));
}
