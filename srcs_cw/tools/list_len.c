#include "../../includes/corewar.h"

int					list_len(t_champ *list)
{
	int				i;
	t_champ			*tmp;

	if (!list)
		return (0);
	i = 0;
	tmp = list;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}
