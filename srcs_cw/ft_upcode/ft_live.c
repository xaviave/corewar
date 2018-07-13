/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_live.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tduverge <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/13 16:02:23 by tduverge     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/13 16:12:51 by tduverge    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/corewar.h"

int			ft_live(t_champ *tmp, t_mem *mem, t_arg *args)
{
	int		name;

	name = -(recup_direct4(mem, tmp, 1));
	tmp->pc = (5 + tmp->pc) % MEM_SIZE;
	if (name > args->nb_players || name <= 0)
		return (-1);
	mem->last_live = name;
	ft_printf(YEL"un processus dit que le joueur %d(%s) est en vie\n"RESET, name,
			args->name[name - 1]);
	tmp->live++;
	return (-1);
}
