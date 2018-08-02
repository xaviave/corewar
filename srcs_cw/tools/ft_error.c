/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_error.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tduverge <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/17 20:33:21 by tduverge     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/24 22:01:19 by tduverge    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/corewar.h"

int		ft_error4(char code, t_champ *tmp, int nu)
{
	int		i;
	int		pc;
	char	test;

	i = -1;
	pc = 2;
	while (++i < nu)
	{
		test = (code >> (6 - i * 2)) & 0b00000011;
		if (test == REG_CODE)
			pc += 1;
		else if (test == DIR_CODE)
			pc += 4;
		else if (test == IND_CODE)
			pc += 2;
	}
	tmp->pc = (tmp->pc + pc) % MEM_SIZE;
	return (-1);
}

int		ft_error2(char code, t_champ *tmp, int nu)
{
	int		i;
	int		pc;
	char	test;

	i = -1;
	pc = 2;
	while (++i < nu)
	{
		test = (code >> (6 - i * 2)) & 0b00000011;
		if (test == REG_CODE)
			pc += 1;
		else if (test == DIR_CODE)
			pc += 2;
		else if (test == IND_CODE)
			pc += 2;
	}
	tmp->pc = (tmp->pc + pc) % MEM_SIZE;
	return (-1);
}
