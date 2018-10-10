/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   give_coline.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xmoreau <xmoreau@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/23 17:28:06 by tduverge     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/02 12:42:30 by lotoussa    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/asm.h"

void			give_coline(char *str, int i, int *tab)
{
	int		j;

	j = 0;
	tab[1] = 1;
	while (j < i)
	{
		tab[0] = 1;
		while (j < i && str[j] != '\n')
		{
			tab[0]++;
			j++;
		}
		if (j == i)
			break ;
		j++;
		tab[1]++;
	}
}
