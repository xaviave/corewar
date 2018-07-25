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

int			ft_ins_type(char *tkn)
{
	if (!ft_strcmp(tkn, "live") || !ft_strcmp(tkn, "zjmp") || !ft_strcmp(tkn, \
				"fork") || !ft_strcmp(tkn, "lfork") || !ft_strcmp(tkn, "aff"))
		return (1);
	if (!ft_strcmp(tkn, "ld") || !ft_strcmp(tkn, "st") ||
			!ft_strcmp(tkn, "lld"))
		return (2);
	return (3);
}

int			ft_check_nb_ins_par(t_list *tmp)
{
	int		c;
	int		par;
	int		sep;

	c = ft_ins_type(((t_compl*)tmp->content)->tkn);
	par = 0;
	sep = 0;
	while (tmp && ft_strcmp(((t_compl*)tmp->content)->tkn, "\n"))
	{
		if (((t_compl*)tmp->content)->type == _PAR)
			par++;
		if (!ft_strcmp(((t_compl*)tmp->content)->tkn, ","))
			sep++;
		tmp = tmp->next;
	}
	if ((c == 1 && par == 1 && sep == 0) || (c == 2 && par == 2 && sep == 1)
			|| (c == 3 && par == 3 && sep == 2))
		return (1);
	return (0);
}
