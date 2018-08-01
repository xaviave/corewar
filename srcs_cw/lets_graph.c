#include "../includes/corewar.h"

int		lets_graph(t_champ **list, t_mem *mem, t_arg *args)
{
	int		very_less;

	mem->c = 0;
	very_less = 0;
	mem->c_todie = CYCLE_TO_DIE;
	mem->c_before_check = mem->c_todie;
	init_window(mem, *list, args);
	while (*list)
	{
		one_cycle(list, mem, args, &very_less);
		print_mem(mem, *list, args, 0);
	}
	print_mem(mem, *list, args, 1);
	getch();
	endwin();
	return (0);
}
