/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_lfork.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tduverge <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/16 21:47:21 by tduverge     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/23 19:15:52 by tduverge    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/corewar.h"

int		ft_lfork(t_champ *tmp, t_champ **list, t_mem *mem, t_arg *args)
{
	t_champ		*fork;
	int			add;

	args = (void*)args;
	fork = ft_memalloc(sizeof(t_champ));
	ft_memcpy(fork, tmp, sizeof(t_champ));
	fork->reg = ft_memalloc(REG_SIZE * REG_NUMBER);
	ft_memcpy(fork->reg, tmp->reg, REG_SIZE * REG_NUMBER);
	fork->next = *list;
	add = recup_direct2(mem, tmp, 1);
	if (add & 0x8000)
		add = (add | 0xFFFF0000) % MEM_SIZE;
	fork->pc = (fork->pc + add + MEM_SIZE) % MEM_SIZE;
	fork->next_instru = -1;
	fork->cycle++;
	*list = fork;
	tmp->pc = mod_pc(tmp, 3);
	fork->id = mem->id;
	mem->id++;
	return (-1);
}
