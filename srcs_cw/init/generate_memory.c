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

void				put_champ_mem(t_champ *list, int player, int nb_player, unsigned char **memory)
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
		(*memory)[i] = (unsigned char)tmp->prog[j];
		i++;
		j++;
	}
}

void				init_aff(t_mem *aff, t_champ **list, int nb_player)
{
	int				i;
	int				champ;
	t_champ			*tmp;

	i = 0;
	champ = 1;
	aff->map = ft_memalloc(sizeof(char *) * MEM_SIZE);
	while (i < MEM_SIZE)
	{
		tmp = *list;
		while (tmp)
		{
			if (champ == tmp->number)
				break ;
			tmp = tmp->next;
		}
		while (i < tmp->prog_size + MEM_SIZE * (champ - 1) / nb_player && i < MEM_SIZE)
		{
			aff->map[i] = (unsigned char)champ;
			i++;
		}
		while (i < MEM_SIZE * champ / nb_player)
			i++;
		champ++;
	}
}

void				generate_memory(t_champ **list, t_mem *aff)
{
	int				i;
	int				nb_player;
	unsigned char	*memory;

	memory = ft_memalloc(sizeof(char *) * MEM_SIZE);
	nb_player = list_len(*list);
	i = 0;
	while (++i <= nb_player)
		put_champ_mem(*list, i, nb_player, &memory);
	aff->memory = memory;
	aff->call_live = 0;
	init_aff(aff, list, nb_player);
}
