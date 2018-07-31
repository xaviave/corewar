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

void		legend(t_champ *list, t_mem *mem, t_arg *args, int col)
{
	int		i;

	i = 0;
	while (i <args->nb_players)
	{
		move(2 * (i + 1), col + 3);
		attron(COLOR_PAIR(i + 1));
		printw("Player %d : %s", i + 1, args->name[i]);
		i++;
	}
	attron(COLOR_PAIR(6));
	attron(A_BOLD);
	move(4 + 2 * (i + 1), col + 3);
	printw("cycle :        %5d", mem->c);
	move(6 + 2 * (i + 1), col + 3);
	printw("cycle to die : %5d", mem->c_todie);
	move(8 + 2 * (i + 1), col + 3);
	printw("processus :    %5d", list_len(list));
	move(10 + 2 * (i + 1), col + 3);
	if (list_len(list))
		printw("LAST LIVE : ");
	else
		printw("The winner is : ");
	attron(COLOR_PAIR(mem->last_live));
	clrtoeol();
	printw("%s", args->name[mem->last_live - 1]);
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
