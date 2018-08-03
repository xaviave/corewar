/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_aff.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tduverge <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/16 21:53:51 by tduverge     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/24 21:02:44 by tduverge    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/corewar.h"

int		ft_aff(t_champ *tmp, t_champ **list, t_mem *mem, t_arg *args)
{
	char			c;
	unsigned int	reg;

	args = (void*)args;
	list = (t_champ **)list;
	if ((mem->memory[(tmp->pc + 1) % MEM_SIZE] & 0xc0) == 64)
	{
		reg = mem->memory[(tmp->pc + 2) % MEM_SIZE];
		if (!reg || reg > REG_NUMBER)
			return (ft_error4(mem->memory[(tmp->pc + 1) % MEM_SIZE], tmp, 1));
		c = give_reg(tmp, reg) % 256;
		if (args->graph == -1 && args->aff == 1)
			ft_printf("Aff: %c\n", c);
		tmp->pc = mod_pc(tmp, 3);
	}
	else
		ft_error4(mem->memory[(tmp->pc + 1) % MEM_SIZE], tmp, 1);
	return (-1);
}
