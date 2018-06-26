/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   generate_memory.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/26 13:13:29 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/26 17:40:47 by xamartin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/corewar.h"

int			list_len(t_champ *list)
{
	int		i;
	t_champ	*tmp;

	i = 0;
	tmp = list;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

void		put_champ_mem(t_champ *list, int player, int nb_player, unsigned char **memory)
{
	int		i;
	int		j;
	t_champ	*tmp;

	j = 0;
	i = MEM_SIZE * (player - 1) / nb_player;
	tmp = list;
	while (tmp && tmp->number != player)
		tmp = tmp->next;
	while (j < tmp->prog_size)
	{
		(*memory)[i] = (unsigned char)tmp->prog[j];
		i++;
		j++;
	}
}

char		*generate_memory(t_champ **list)
{
	int		i;
	int		nb_player;
	unsigned char	*memory;

	memory = ft_memalloc(sizeof(char *) * MEM_SIZE);
	nb_player = list_len(*list);
	i = 0;
	while (++i <= nb_player)
		put_champ_mem(*list, i, nb_player, &memory);
	i = 0;
	while (i < MEM_SIZE)
	{
		if (i % 2 == 0 && i != 0)
		{
			if (i % 64 == 0)
				ft_printf("\n");
			else
				ft_printf(" ");
		}
		ft_printf("%02x", memory[i]);
		i++;
	}
	return ((char *)memory);
}
