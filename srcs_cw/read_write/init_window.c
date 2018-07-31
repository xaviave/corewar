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
	"Speed Max",
	"Speed x2",
	"Speed x1",
	"Step by step",
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
	mem->speed = -(1 - choice) * 10000;
	refresh();
	free(menu_win);
}


void	init_window(t_mem *mem, t_champ *list, t_arg *args)
{
	initscr();
	clear();
	noecho();
	cbreak(); 
	start_color();
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_BLUE, COLOR_BLACK);
	init_pair(3, COLOR_RED, COLOR_BLACK);
	init_pair(4, COLOR_CYAN, COLOR_BLACK);
	init_pair(5, COLOR_WHITE, COLOR_BLACK);
	init_menu(mem);
	print_mem(mem, list, args);
}
