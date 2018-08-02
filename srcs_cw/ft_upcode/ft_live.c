/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_live.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tduverge <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/13 16:02:23 by tduverge     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/19 18:27:08 by tduverge    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/corewar.h"

int			ft_live(t_champ *tmp, t_champ **list, t_mem *mem, t_arg *args)
{
	int		name;

	list = (t_champ **)list;
	name = -(recup_direct4(mem, tmp, 1));
	tmp->pc = mod_pc(tmp, 5);
	mem->call_live++;
	tmp->live++;
	if (name > args->nb_players || name <= 0)
		return (-1);
	if (args->aff == 1 && args->graph == -1)
		ft_printf("un processus dit que le joueur %d(%s) est en vie\n", name,
				args->name[name - 1]);
	mem->last_live = name;
	(mem->player_live[name - 1])++;
	mem->player_last[name - 1] = mem->c;
	return (-1);
}
