/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print_mem.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tduverge <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/13 16:24:08 by tduverge     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/13 16:26:53 by tduverge    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void	print_mem(t_mem *mem)
{
	int	i;

	i = -1;
	while (++i < MEM_SIZE)
	{
		if (i)
		{
			if (i % 64 == 0)
				ft_printf("\n");
		}
		if (mem->map[i] == 1)
			ft_printf(RED"");
		if (mem->map[i] == 2)
			ft_printf(BLUE"");
		ft_printf("%02x "RESET, mem->memory[i]);
	}
	ft_printf("\n");
}
