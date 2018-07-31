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
	return (line);
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

void		print_mem(t_mem *mem, t_champ *list, t_arg *args)
{
	int			line;

	line = without_process(mem);
	draw_process(mem, list);
	attron(COLOR_PAIR(2));
	move(line + 1, 0);
	printw("cycle : %d | cycle to die : %d | processus : %d			",
		mem->c, mem->c_todie, list_len(list));
	refresh();
	if (args->dump != -1 && mem->c < args->dump)
		return ;
	if (mem->speed == 30000)
		getch();
	else if (mem->speed)
		usleep(mem->speed);
}
