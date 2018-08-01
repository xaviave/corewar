/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print_mem.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tduverge <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/13 16:24:08 by tduverge     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/24 21:12:35 by tduverge    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/corewar.h"

int			without_process(t_mem *mem)
{
	int		i;
	int		line;
	int		col;

	i = -1;
	line = 0;
	col = 0;
	move(line, col);
	refresh();
	while (++i < MEM_SIZE)
	{
		if (i && i % 64 == 0)
		{
			line++;
			col = 0;
			move(line, col);
		}
		attron(COLOR_PAIR(mem->map[i] == 0 ? 5 : mem->map[i]));
		printw("%02x ", mem->memory[i]);
		col += 3;
		move(line, col);
	}
	return (col);
}

void		draw_process(t_mem *mem, t_champ *list)
{
	t_champ		*tmp;

	tmp = list;
	while (tmp)
	{
		move(tmp->pc / 64, (tmp->pc % 64) * 3);
		attron(COLOR_PAIR(mem->map[tmp->pc]));
		attron(A_STANDOUT);
		printw("%02x", mem->memory[tmp->pc]);
		attroff(COLOR_PAIR(mem->map[tmp->pc]));
		tmp = tmp->next;
	}
	attroff(A_STANDOUT);
}

void		draw_breakdown(t_mem *mem, int col, int line)
{
	int		i;
	int		j;
	int		limit[4];

	i = -1;
	j = 0;
	while (++i < 4)
		j += mem->player_live[i];
	limit[0] = j == 0 ? 0 : 33 * mem->player_live[0] / j;
	limit[1] = j == 0 ? 0 : 33 * mem->player_live[1] / j + limit[0];
	limit[2] = j == 0 ? 0 : 33 * mem->player_live[2] / j + limit[1];
	limit[3] = j == 0 ? 0 : 33 * mem->player_live[3] / j + limit[2];
	i = -1;
	j = 0;
	move(line, col + 3);
	while (++i < 33)
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

void		legend(t_champ *list, t_mem *mem, t_arg *args, int col)
{
	int		i;

	i = 0;
	attron(A_BOLD);
	attron(COLOR_PAIR(6));
	move(1, col + 3);
	printw("Cycle :                     %5d", mem->c);
	move(4, col + 3);
	printw("Cycle Before Check :        %5d", mem->c_before_check);
	move(6, col + 3);
	printw("Cycle To Die :              %5d", mem->c_todie);
	move(8, col + 3);
	printw("Processus :                 %5d", list_len(list));
	while (i <args->nb_players)
	{
		move(4 * i + 11, col + 3);
		attron(COLOR_PAIR(i + 1));
		printw("Player %d : %s", i + 1, args->name[i]);
		attron(COLOR_PAIR(5));
		move(4 * i + 12, col + 3);
		printw("Last live :                 %5d", mem->player_last[i]);
		move(4 * i + 13, col + 3);
		printw("Live in current period :    %5d", mem->player_live[i]);
		i++;
	}
	move(4 * i + 21, col + 3);
	if (list_len(list))
		printw("Last live : ");
	else
		printw("The WINNER is : ");
	attron(COLOR_PAIR(mem->last_live));
	clrtoeol();
	printw("%s !", args->name[mem->last_live - 1]);
	move(4 * i + 15, col + 3);
	attron(COLOR_PAIR(5));
	printw("Live breakdown for current period :");
	draw_breakdown(mem, col, 4 * i + 16);
	if (mem->c_before_check == 0)
	{
		attron(COLOR_PAIR(5));
		move(4 * i + 18, col + 3);
		printw("Live breakdown for last period :");
		draw_breakdown(mem, col, 4 * i + 19);
	}
	attroff(A_BOLD);
}

void		print_mem(t_mem *mem, t_champ *list, t_arg *args)
{
	int			col;

	col = without_process(mem);
	draw_process(mem, list);
	legend(list, mem, args, col);
	refresh();
	if (args->dump != -1 && mem->c < args->dump)
		return ;
	if (mem->speed == 30000)
		getch();
	else if (mem->speed)
		usleep(mem->speed);
}
