#include "../includes/asm.h"

int			ft_del_sep(t_list **list, int i, char *tkn)
{
	t_list		*tmp;
	t_list		*buf;

	tmp = *list;
	while (tmp && i && ft_strcmp(((t_compl*)tmp->next->content)->tkn, tkn))
	{
		tmp = tmp->next;
		i--;
	}
	buf = tmp->next;
	tmp->next = tmp->next->next;
	ft_strdel(&((t_compl*)buf->content)->tkn);
	((t_compl*)buf->content)->type = 0;
	((t_compl*)buf->content)->par_type = 0;
	((t_compl*)buf->content)->line = 0;
	free(((t_compl*)buf->content));
	free(buf);
	buf = NULL;
	return (1);
}

int			ft_reform(t_all *a)
{
	t_list		*tmp;
	int			i;

	tmp = a->t;
	i = 0;
	while (tmp)
	{
		if (((t_compl*)tmp->content)->type == _SEP)
			ft_del_sep(&a->t, i, ((t_compl*)tmp->content)->tkn);
		tmp = tmp->next;
		i++;
	}
	return (1);
}
