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

int			control(t_mem *mem, int key)
{
	if (key == KEY_SPACE)
		return (0);
	else if (key == KEY_R && mem->speed < 990)
		mem->speed += 10;
	else if (key == KEY_R)
		mem->speed = 1000;
	else if (key == KEY_E && mem->speed < 999)
		mem->speed += 1;
	else if (key == KEY_E)
		mem->speed = 1000;
	else if (key == KEY_W && mem->speed > 1)
		mem->speed -= 1;
	else if (key == KEY_W)
		mem->speed = 1;
	else if (key == KEY_Q && mem->speed > 10)
		mem->speed -= 10;
	else if (key == KEY_Q)
		mem->speed = 1;
	move(2, 195);
	attron(COLOR_PAIR(6));
	attron(A_BOLD);
	printw("Speed :                       %5d", mem->speed);
	attroff(COLOR_PAIR(6));
	attroff(A_BOLD);
	return (1);
}

void		print_mem(t_mem *mem, t_champ *list, t_arg *args, int stop)
{
	int			col;
	int			key;

	col = without_process(mem);
	draw_process(mem, list);
	legend(list, mem, args, col);
	refresh();
	if (args->dump != -1 && mem->c < args->dump)
		return ;
	key = getch();
	col = 1;
	if (key == KEY_SPACE || stop)
		while (col || control(mem, key))
		{
			key = getch();
			col = 0;
		}
	else
		control(mem, key);
	usleep(1000000 / mem->speed);
}
