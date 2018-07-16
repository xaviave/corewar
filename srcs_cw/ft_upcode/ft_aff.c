/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_aff.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tduverge <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/16 21:53:51 by tduverge     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/16 23:32:37 by tduverge    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/corewar.h"

int		ft_aff(t_champ *tmp, t_champ *list, t_mem *mem, t_arg *args)
{
	char			c;
	unsigned int	reg;

	args = (void*)args;
	if (mem->memory[(tmp->pc + 1) % MEM_SIZE] == 64)
	{
		reg = mem->memory[(tmp->pc + 2) % MEM_SIZE];
		if (!reg || reg > 16)
			return (-1);
		c = give_reg(tmp, reg) % 256;
		ft_putchar(c);
		tmp->pc = mod_pc(tmp, list, mem, 3);
	}
	return (-1);
}
