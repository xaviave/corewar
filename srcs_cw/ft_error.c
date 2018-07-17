/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_error.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tduverge <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/17 20:33:21 by tduverge     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/17 20:47:30 by tduverge    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/corewar.h"

int		ft_error(char code, t_champ *tmp, int ret)
{
	int	i;
	int	pc;

	i = -1;
	pc = 2;
	while (++i < 2)
	{
		if (!i)
			code = (code >> 6) & 0b00000011;
		else
			code = (code >> 4) & 0b00000011;
		if (code == REG_CODE)
			pc += 1;
		else if (code == DIR_CODE)
			pc += 4;
		else if (code == IND_CODE)
			pc += 2;
	}
	tmp->pc = (tmp->pc + pc) % MEM_SIZE;
	return (ret);
}
