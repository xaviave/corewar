/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   kill_them_all.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tduverge <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/22 14:23:03 by tduverge     #+#   ##    ##    #+#       */
/*   Updated: 2018/08/22 14:23:04 by tduverge    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void	kill_them_all(t_champ **list)
{
	t_champ		*tmp;

	tmp = *list;
	while (*list)
	{
		tmp = *list;
		*list = (*list)->next;
		free(tmp->reg);
		free(tmp);
	}
}
