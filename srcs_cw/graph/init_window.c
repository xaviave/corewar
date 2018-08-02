/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   init_window.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tduverge <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/18 13:27:40 by tduverge     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/23 11:36:59 by tduverge    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/corewar.h"

char *choices[] =
{
	"Speed x1000",
	"Speed x500",
	"Speed x50",
	"Speed x1",
};

void print_menu(WINDOW *menu_win, int highlight)
{
	int x;
	int y;
	int i;

	i = -1;
	x = 2;
	y = 2;
	box(menu_win, 0, 0);
	while (++i < (int)(sizeof(choices) / sizeof(char *)))
	{
		if (highlight == i + 1)
		{
			wattron(menu_win, A_REVERSE); 
			mvwprintw(menu_win, y, x, "%s", choices[i]);
			wattroff(menu_win, A_REVERSE);
		}
		else
			mvwprintw(menu_win, y, x, "%s", choices[i]);
		++y;
	}
	move(0, COLS);
	wrefresh(menu_win);
}

void init_menu(t_mem *mem)
{
	WINDOW *menu_win;
	int highlight;
	int choice;
	int c;

	choice = 0;
	highlight = 1;
	initscr();
	clear();
	noecho();
	cbreak();
	menu_win = newwin(8, 20, 20, 40);
	keypad(menu_win, TRUE);
	mvprintw(0, 0, "Use arrow keys to go up and down, Press enter to select a choice");
	refresh();
	print_menu(menu_win, highlight);
	while(1)
	{c = wgetch(menu_win);
		switch(c)
		{case KEY_UP:
			if(highlight == 1)
				highlight = sizeof(choices) / sizeof(char *);
			else
				--highlight;
			break;
			case KEY_DOWN:
			if(highlight == sizeof(choices) / sizeof(char *))
				highlight = 1;
			else 
				++highlight;
			break;
			case 10:
			choice = highlight;
			break;
			default:
			refresh();
			break;
		}
		print_menu(menu_win, highlight);
		if(choice != 0)
			break;
	}
	mem->speed = (117 * ft_pow(choice, 3) - 652 * ft_pow(choice, 2) +
													137 * choice + 2398) / 2;
	refresh();
	free(menu_win);
}

void		print_command()
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

void	init_window(t_mem *mem, t_champ *list, t_arg *args, int *stop)
{
	initscr();
	signal(SIGWINCH, NULL);
	clear();
	noecho();
	cbreak(); 
	start_color();
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_BLUE, COLOR_BLACK);
	init_pair(3, COLOR_RED, COLOR_BLACK);
	init_pair(4, COLOR_CYAN, COLOR_BLACK);
	init_pair(5, COLOR_WHITE, COLOR_BLACK);
	init_pair(6, COLOR_YELLOW, COLOR_BLACK);
	init_menu(mem);
	nodelay(stdscr, 1);
	print_command();
	*stop = print_mem(mem, list, args, 1);
}
