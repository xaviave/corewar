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
	//tmp->pc = (5 + tmp->pc) % MEM_SIZE;
	if (name > args->nb_players || name <= 0)
	{
	//	ft_putstr("------------------------------------------------------------ LIVE !!!\n");
		return (-1);
	}
	mem->last_live = name;
	/*
	ft_putstr(YEL"un processus dit que le joueur ");
	ft_putnbr(name);
	ft_putchar('(');
	ft_putstr(args->name[name - 1]);
	ft_putstr(") est en vie\n"RESET);
	*/
	return (-1);
}
