/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   legend.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tduverge <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/22 14:18:57 by tduverge     #+#   ##    ##    #+#       */
/*   Updated: 2018/08/22 14:20:20 by tduverge    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void			info_cycle(t_champ *list, t_mem *mem)
{
	attron(A_BOLD);
	attron(COLOR_PAIR(6));
	move(1, 195);
	printw("Cycle :                       %5d", mem->c);
	move(3, 195);
	printw("Cycles/second limit :         %5d", mem->speed);
	move(7, 195);
	printw("Cycles Before Check :         %5d", mem->c_before_check);
	move(9, 195);
	printw("Cycle To Die :                %5d", mem->c_todie);
	move(11, 195);
	printw("Processus :                   %5d", list_len(list));
	attroff(A_BOLD);
	attroff(COLOR_PAIR(6));
}

static int		info_players(t_champ *list, t_mem *mem, t_arg *args, int col)
{
	int		i;

	i = 0;
	while (i < args->nb_players)
	{
		move(4 * i + 14, col + 3);
		attron(COLOR_PAIR(i + 1));
		printw("Player %d : %s", i + 1, args->name[i]);
		attron(COLOR_PAIR(5));
		move(4 * i + 15, col + 3);
		printw("Last live :                   %5d", mem->player_last[i]);
		move(4 * i + 16, col + 3);
		printw("Live in current period :      %5d", mem->player_live[i]);
		i++;
	}
	move(4 * i + 25, col + 3);
	if (list_len(list))
		printw("Last live : ");
	else
		printw("The WINNER is : ");
	attron(COLOR_PAIR(mem->last_live));
	clrtoeol();
	printw("%s !", args->name[mem->last_live - 1]);
	return (i);
}

static void		draw_breakdown(int col, int line, int *limit)
{
	int		i;
	int		j;

	i = -1;
	j = 0;
	move(line, col + 3);
	while (++i < 35)
	{
		if (j < limit[0])
			attron(COLOR_PAIR(1));
		else if (j < limit[1])
			attron(COLOR_PAIR(2));
		else if (j < limit[2])
			attron(COLOR_PAIR(3));
		else if (j < limit[3])
			attron(COLOR_PAIR(4));
		printw("-");
		j++;
	}
}

static void		info_breakdown(t_mem *mem, int col, int i)
{
	int			a;
	int			nb_live;
	int			limit[4];

	a = -1;
	nb_live = 0;
	while (++a < 4)
		nb_live += mem->player_live[a];
	limit[0] = nb_live == 0 ? 0 : 35 * mem->player_live[0] / nb_live;
	limit[1] = nb_live == 0 ? 0 : 35 * mem->player_live[1] / nb_live + limit[0];
	limit[2] = nb_live == 0 ? 0 : 35 * mem->player_live[2] / nb_live + limit[1];
	limit[3] = nb_live == 0 ? 0 : 35 * mem->player_live[3] / nb_live + limit[2];
	move(4 * i + 19, col + 3);
	attron(COLOR_PAIR(5));
	printw("Live breakdown for current period :");
	draw_breakdown(col, 4 * i + 20, limit);
	if (mem->c_before_check == 0)
	{
		attron(COLOR_PAIR(5));
		move(4 * i + 22, col + 3);
		printw("Live breakdown for last period :");
		draw_breakdown(col, 4 * i + 23, limit);
	}
}

void			legend(t_champ *list, t_mem *mem, t_arg *args, int col)
{
	int		i;

	attron(A_BOLD);
	attron(COLOR_PAIR(6));
	info_cycle(list, mem);
	i = info_players(list, mem, args, col);
	info_breakdown(mem, col, i);
	attroff(A_BOLD);
}
