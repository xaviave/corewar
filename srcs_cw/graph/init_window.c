/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   init_window.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tduverge <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/18 13:27:40 by tduverge     #+#   ##    ##    #+#       */
/*   Updated: 2018/08/22 14:14:53 by tduverge    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/corewar.h"

static void		print_command(void)
{
	attron(COLOR_PAIR(5));
	move(52, 195);
	printw("/************ COMMAND ************\\");
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

void			init_window(t_mem *mem, t_champ *list, t_arg *args, int *stop)
{
	initscr();
	signal(SIGWINCH, NULL);
	clear();
	noecho();
	cbreak();
	start_color();
	mem->speed = 50;
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_BLUE, COLOR_BLACK);
	init_pair(3, COLOR_RED, COLOR_BLACK);
	init_pair(4, COLOR_CYAN, COLOR_BLACK);
	init_pair(5, COLOR_WHITE, COLOR_BLACK);
	init_pair(6, COLOR_YELLOW, COLOR_BLACK);
	nodelay(stdscr, 1);
	print_command();
	*stop = print_mem(mem, list, args, 1);
}
