#include "../../includes/corewar.h"

void	kill_them_all(t_champ **list)
{
	t_champ		*tmp;

	tmp = *list;
	while (*list)
	{
		tmp = *list;
		*list = (*list)->next;
		free(tmp->reg);
		free(tmp);
	}
}
