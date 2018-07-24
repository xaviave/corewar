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

void	print_mem(t_mem *mem, t_champ *list)
{
	//return ;
	int	i;
	int	line;
	int	col;

	i = -1;
	line = 0;
	col = 0;
	move(line, col);
	refresh();
	while (++i < MEM_SIZE)
	{
		if (i)
		{
			if (i % 64 == 0)
			{
				line++;
				col = 0;
				move(line, col);
			}
		}
		if (mem->map[i] == 1)
			attron(COLOR_PAIR(1));
		else if (mem->map[i] == 2)
			attron(COLOR_PAIR(2));
		printw("%02x ", mem->memory[i]);
		attroff(COLOR_PAIR(1));
		attroff(COLOR_PAIR(2));
		col += 3;
		move(line, col);
	}
	t_champ *tmp;

	tmp = list;
	while (tmp)
	{
		move(tmp->pc / 64, (tmp->pc % 64) * 3);
		if (mem->map[tmp->pc] == 1)
			attron(COLOR_PAIR(1));
		else if (mem->map[tmp->pc] == 2)
			attron(COLOR_PAIR(2));
		attron(A_STANDOUT);
		printw("%02x", mem->memory[tmp->pc]);
		attroff(A_STANDOUT);
		attroff(COLOR_PAIR(1));
		attroff(COLOR_PAIR(2));
		tmp = tmp->next;
	}
	attron(COLOR_PAIR(2));
	move(line + 1, 0);
	printw("cycle : %d | cycle to die : %d | processus : %d			", mem->c, mem->c_todie, list_len(list));
	attroff(COLOR_PAIR(2));
	refresh();
	/*
	if (mem->c < 10540)
		return ;
		*/
	if (mem->speed == 30000)
		getch();
	else if (mem->speed)
		usleep(mem->speed);
}
