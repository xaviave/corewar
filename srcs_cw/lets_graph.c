#include "../includes/corewar.h"

int		lets_graph(t_champ **list, t_mem *mem, t_arg *args)
{
	int		tmp;
	int		less;
	int		very_less;

	mem->c = 0;
	very_less = 0;
	mem->c_todie = CYCLE_TO_DIE;
	tmp = mem->c_todie;
	init_window(mem, *list);
	while (*list)
	{
		if (mem->c_todie ==  0)
		{
			less = check_live(list);
			if (mem->call_live >= NBR_LIVE || very_less == MAX_CHECKS - 1)
			{
				mem->c_todie = tmp - CYCLE_DELTA;
				tmp = mem->c_todie;
				very_less = 0;
			}
			else
			{
				very_less++;
				mem->c_todie = tmp;
			}
			mem->call_live = 0;
			if (mem->c_todie < 0)
				kill_them_all(list);
		}
		check_cycle(list, mem, mem->c, args);
		mem->c_todie--;
		mem->c++;
		print_mem(mem, *list);
	}
	print_mem(mem, *list);
	getch();
	endwin();
	return (0);
}
