/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print_mem.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tduverge <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/13 16:24:08 by tduverge     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/16 18:02:34 by tduverge    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/corewar.h"

#include "stdio.h"

void	print_mem(t_mem *mem, t_champ *list)
{
	int	i;

	i = -1;
	//return ;
				printf("\n\n\n");
	while (++i < MEM_SIZE)
	{
		if (i)
		{
			if (i % 64 == 0)
				printf("\n");
		}
		if (mem->map[i] == 1)
			printf(RED"");
		if (mem->map[i] == 2)
			printf(BLUE"");
		else
			printf(GREY"");
		printf("%02x "RESET, mem->memory[i]);
	}
	printf("\n");
	list = (t_champ *)list;
}
