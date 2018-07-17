/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_fork.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tduverge <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/16 21:23:33 by tduverge     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/17 15:11:11 by tduverge    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/corewar.h"

int		ft_fork(t_champ *tmp, t_champ *list, t_mem *mem, t_arg *args)
{
	t_champ		*fork;
	t_champ		*last;
	int			add;

	args = (void*)args;
	fork = ft_memalloc(sizeof(t_champ));
	ft_memcpy(fork, tmp, sizeof(t_champ));
	fork->reg = ft_memalloc(REG_SIZE * REG_NUMBER);
	ft_memcpy(fork->reg, tmp->reg, REG_SIZE * REG_NUMBER);
	fork->next = NULL;
	add = recup_direct2(mem, tmp, 1);
	if (add & 0x8000)
		add = add % IDX_MOD - 512;
	else
		add = add % IDX_MOD;
	fork->pc = (fork->pc + add % IDX_MOD) % MEM_SIZE;
	fork->next_instru = -1;
	fork->cycle++;
	last = list;
	while (last->next)
		last = last->next;
	last->next = fork;
	tmp->pc = mod_pc(tmp, list, mem, 3);
	return (-1);
}
