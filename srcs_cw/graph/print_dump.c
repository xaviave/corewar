/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print_dump.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tduverge <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/23 17:08:31 by tduverge     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/23 17:52:54 by tduverge    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void	print_dump(t_mem *mem)
{
	int		i;
	int		enter;

	i = 0;
	enter = 1;
	while (i < MEM_SIZE)
	{
		ft_printf("0x%04x : ", i);
		while (enter || i % 64)
		{
			ft_printf("%02x ", mem->memory[i]);
			enter = 0;
			i++;
		}
		ft_printf("\n");
		enter = 1;
	}
}
