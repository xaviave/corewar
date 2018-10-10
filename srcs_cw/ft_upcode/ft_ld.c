/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_ld.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tduverge <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/13 16:02:36 by tduverge     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/24 21:04:00 by tduverge    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/corewar.h"

static int		first_case(t_champ *tmp, t_mem *mem)
{
	int		value;
	int		reg;

	value = recup_direct4(mem, tmp, 2);
	reg = (int)mem->memory[(tmp->pc + 6) % MEM_SIZE];
	tmp->pc = mod_pc(tmp, 7);
	if (reg <= 0 || reg > 16)
		return (-1);
	write_reg(tmp, reg, value);
	return (value == 0 ? 1 : 0);
}

static int		second_case(t_champ *tmp, t_mem *mem)
{
	int		value;
	int		reg;

	value = recup_indirect4x(mem, tmp, 2);
	reg = (int)mem->memory[(tmp->pc + 4) % MEM_SIZE];
	tmp->pc = mod_pc(tmp, 5);
	if (reg <= 0 || reg > 16)
		return (-1);
	write_reg(tmp, reg, value);
	return (value == 0 ? 1 : 0);
}

int				ft_ld(t_champ *tmp, t_champ **list, t_mem *mem, t_arg *args)
{
	list = (t_champ **)list;
	args = (t_arg *)args;
	if ((mem->memory[(tmp->pc + 1) % MEM_SIZE] & 0xf0) == 144)
		return (first_case(tmp, mem));
	else if ((mem->memory[(tmp->pc + 1) % MEM_SIZE] & 0xf0) == 208)
		return (second_case(tmp, mem));
	else
		return (ft_error4(mem->memory[(tmp->pc + 1) % MEM_SIZE], tmp, 2));
}
