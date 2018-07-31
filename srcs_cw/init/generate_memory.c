/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   generate_memory.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/26 13:13:29 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/17 14:11:57 by tduverge    ###    #+. /#+    ###.fr     */
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

void				put_champ_mem(t_champ *list, int player, int nb_player, t_mem *mem)
{
	int				i;
	int				j;
	t_champ			*tmp;

	j = 0;
	i = MEM_SIZE * (player - 1) / nb_player;
	tmp = list;
	while (tmp && tmp->number != player)
		tmp = tmp->next;
	tmp->pc = i;
	while (j < tmp->prog_size)
	{
		(mem->memory)[i] = (unsigned char)tmp->prog[j];
		(mem->map)[i] = tmp->number;
		i++;
		j++;
	}
}

void				generate_memory(t_champ **list, t_mem *mem)
{
	int				i;
	int				nb_player;

	mem->memory = ft_memalloc(sizeof(char *) * MEM_SIZE);
	mem->map = ft_memalloc(sizeof(char *) * MEM_SIZE);
	mem->call_live = 0;
	nb_player = list_len(*list);
	i = 0;
	while (++i <= nb_player)
		put_champ_mem(*list, i, nb_player, mem);
}
