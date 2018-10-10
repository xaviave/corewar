/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   list_len.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tduverge <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/22 14:23:16 by tduverge     #+#   ##    ##    #+#       */
/*   Updated: 2018/08/22 14:23:18 by tduverge    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/corewar.h"

int					list_len(t_champ *list)
{
	int				i;
	t_champ			*tmp;

	if (!list)
		return (0);
	i = 0;
	tmp = list;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}
