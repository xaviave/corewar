/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   access_reg.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tduverge <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/20 17:56:17 by tduverge     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/13 16:16:11 by tduverge    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/corewar.h"

int		give_reg(t_champ *champ, int number)
{
	int		ret;

	ret = 0;
	ft_memcpy(&ret, champ->reg + REG_SIZE * (number - 1), REG_SIZE);
	return (ret);
}

void	write_reg(t_champ *champ, int nb_of_reg, int nb_to_write)
{
	ft_memcpy(champ->reg + REG_SIZE * (nb_of_reg - 1), &nb_to_write, REG_SIZE);
}
