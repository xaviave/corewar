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
		return (1);
	else if (key == KEY_S)
		return (2);
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
	move(3, 195);
	attron(COLOR_PAIR(6));
	attron(A_BOLD);
	printw("Cycles/second limit :         %5d", mem->speed);
	attroff(COLOR_PAIR(6));
	attroff(A_BOLD);
	return (0);
}

void		print_command(int stop)
{
	attron(COLOR_PAIR(5));
	move(50, 195);
	if (stop)
		printw("\\***** PAUSED *****//");
	else
		printw("                      ");
	move(52, 195);
	printw("/*************Command*************\\");
	move(53, 195);
	printw("|                                 |");
	move(54, 195);
	printw("| Q :     -10 speed               |");
	move(55, 195);
	printw("| W :      -1 speed               |");
	move(56, 195);
	printw("| E :      +1 speed               |");
	move(57, 195);
	printw("| R :     +10 speed               |");
	move(58, 195);
	printw("|                                 |");
	move(59, 195);
	printw("| Space : Start and Stop          |");
	move(60, 195);
	printw("| S :     Next step               |");
	move(61, 195);
	printw("|                                 |");
	move(62, 195);
	printw("\\*********************************/");
}

int			print_mem(t_mem *mem, t_champ *list, t_arg *args, int stop)
{
	int			col;
	int			key;

	col = without_process(mem);
	draw_process(mem, list);
	legend(list, mem, args, col);
	refresh();
	if (args->dump != -1 && mem->c < args->dump)
		return (0);
	key = getch();
	col = 1;
	if (key == KEY_SPACE || stop)
	{
		print_command(1);
		while (col || !(stop = control(mem, key)))
		{
			col = 0;
			key = getch();
		}
		print_command(0);
	}
	else
		control(mem, key);
	usleep(1000000 / mem->speed);
	return (stop == 2 ? 1 : 0);
}
