/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_sub.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tduverge <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/16 18:22:54 by tduverge     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/23 15:21:27 by tduverge    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/corewar.h"

int		ft_sub(t_champ *tmp, t_champ **list, t_mem *mem, t_arg *args)
{
	int					value1;
	int					value2;
	unsigned int		reg[3];

	args = (t_arg *)args;
	reg[0] = mem->memory[(tmp->pc + 2) % MEM_SIZE];
	reg[1] = mem->memory[(tmp->pc + 3) % MEM_SIZE];
	reg[2] = mem->memory[(tmp->pc + 4) % MEM_SIZE];
	if (mem->memory[(tmp->pc + 1) % MEM_SIZE] == 84 && reg[0] && reg[1] &&
			reg[2] && reg[0] < 17 && reg[1] < 17 && reg[2] < 17)
	{
		value1 = give_reg(tmp, reg[0]);
		value2 = give_reg(tmp, reg[1]);
		write_reg(tmp, reg[2], value1 - value2);
		tmp->pc = mod_pc(tmp, *list, mem, 5);
		return (value1 - value2 == 0 ? 1 : 0);
	}
		return (ft_error(mem->memory[(tmp->pc + 1) % MEM_SIZE], tmp, 0));
}
