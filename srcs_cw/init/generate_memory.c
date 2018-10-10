/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   generate_memory.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/26 13:13:29 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2018/08/22 16:56:30 by tduverge    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/corewar.h"

static void	put_champ_mem(t_champ *list, int player, int nb_player, t_mem *mem)
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

static void	init_instru(t_mem *mem)
{
	mem->instru[0] = &ft_live;
	mem->instru[1] = &ft_ld;
	mem->instru[2] = &ft_st;
	mem->instru[3] = &ft_add;
	mem->instru[4] = &ft_sub;
	mem->instru[5] = &ft_and;
	mem->instru[6] = &ft_or;
	mem->instru[7] = &ft_xor;
	mem->instru[8] = &ft_zjmp;
	mem->instru[9] = &ft_ldi;
	mem->instru[10] = &ft_sti;
	mem->instru[11] = &ft_fork;
	mem->instru[12] = &ft_lld;
	mem->instru[13] = &ft_lldi;
	mem->instru[14] = &ft_lfork;
	mem->instru[15] = &ft_aff;
}

static void	init_time(t_mem *mem)
{
	mem->times[0] = 10;
	mem->times[1] = 5;
	mem->times[2] = 5;
	mem->times[3] = 10;
	mem->times[4] = 10;
	mem->times[5] = 6;
	mem->times[6] = 6;
	mem->times[7] = 6;
	mem->times[8] = 20;
	mem->times[9] = 25;
	mem->times[10] = 25;
	mem->times[11] = 800;
	mem->times[12] = 10;
	mem->times[13] = 50;
	mem->times[14] = 1000;
	mem->times[15] = 2;
}

void		generate_memory(t_champ **list, t_mem *mem, t_arg *args)
{
	int				i;
	int				nb_player;

	mem->memory = ft_memalloc(sizeof(char *) * MEM_SIZE);
	mem->map = ft_memalloc(sizeof(char *) * MEM_SIZE);
	ft_bzero(mem->player_last, sizeof(int) * MAX_PLAYERS);
	ft_bzero(mem->player_live, sizeof(int) * MAX_PLAYERS);
	mem->call_live = 0;
	mem->last_live = args->nb_players;
	init_time(mem);
	init_instru(mem);
	nb_player = list_len(*list);
	i = 0;
	while (++i <= nb_player)
		put_champ_mem(*list, i, nb_player, mem);
}
