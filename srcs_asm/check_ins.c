#include "../includes/asm.h"

int			ft_check_nb_ins_line(t_list *tmp, t_list **list)
{
	int		c;
	t_list	*l;

	c = 0;
	l = *list;
	while (((t_compl*)l->content)->line != ((t_compl*)tmp->content)->line)
		l = l->next;
	tmp = l;
	if (!ft_strcmp(((t_compl*)tmp->content)->tkn, "\n"))
		tmp = tmp->next;
	while (tmp && ft_strcmp(((t_compl*)tmp->content)->tkn, "\n"))
	{
		if (((t_compl*)tmp->content)->type == _INS)
			c++;
		tmp = tmp->next;
	}
	return (c == 1 ? 1 : 0);
}
