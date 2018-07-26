#include "../includes/asm.h"

void		ft_ins_dont_move(char *tkn, t_list **tmp, int *size)
{
	t_list		*inc;

	inc = *tmp;
	if (!ft_strcmp(tkn, "aff") || !ft_strcmp(tkn, "lfork")
			|| !ft_strcmp(tkn, "fork") || !ft_strcmp(tkn, "zjmp"))
	{
		while (inc && ft_strcmp(((t_compl*)inc->content)->tkn, "\n"))
			inc = inc->next;
		*tmp = (inc->next ? inc->next : inc);
		*size += 3;
	}
	else if (!ft_strcmp(tkn, "live") || !ft_strcmp(tkn, "add")
			|| !ft_strcmp(tkn, "sub"))
	{
		while (inc && ft_strcmp(((t_compl*)inc->content)->tkn, "\n"))
			inc = inc->next;
		*tmp = (inc->next ? inc->next : inc);
		*size += 5;
	}
}

void		ft_ins_ott(char *tkn, t_list **tmp, int *size)
{
	t_list		*inc;

	inc = *tmp;
	if (!ft_strcmp(tkn, "ldi") || !ft_strcmp(tkn, "sti")
			|| !ft_strcmp(tkn, "lldi"))
	{
		*size += 2;
		while (inc && ft_strcmp(((t_compl*)inc->content)->tkn, "\n"))
		{
			if (((t_compl*)inc->content)->par_type == _REG)
				*size += 1;
			else if (((t_compl*)inc->content)->par_type == _DIR
					|| ((t_compl*)inc->content)->par_type == _IND)
				*size += 2;
			inc = inc->next;
		}
		*tmp = (inc->next ? inc->next : inc);
	}
}

void		ft_ins_oft(char *tkn, t_list **tmp, int *size)
{
	t_list		*inc;

	inc = *tmp;
	if (!ft_strcmp(tkn, "and") || !ft_strcmp(tkn, "or")
			|| !ft_strcmp(tkn, "xor") || !ft_strcmp(tkn, "lld"))
	{
		*size += 2;
		while (inc && ft_strcmp(((t_compl*)inc->content)->tkn, "\n"))
		{
			if (((t_compl*)inc->content)->par_type == _REG)
				*size += 1;
			else if (((t_compl*)inc->content)->par_type == _DIR)
				*size += 4;
			else if (((t_compl*)inc->content)->par_type == _IND)
				*size += 2;
			inc = inc->next;
		}
		*tmp = (inc->next ? inc->next : inc);
	}
}

int			ft_count_every_line(t_list **list)
{
	t_list		*tmp;
	int			size;

	tmp = *list;
	size = 0;
	while (tmp)
	{
		ft_ins_dont_move(((t_compl*)tmp->content)->tkn, &tmp, &size);
		ft_ins_ott(((t_compl*)tmp->content)->tkn, &tmp, &size);
		ft_ins_oft(((t_compl*)tmp->content)->tkn, &tmp, &size);
		ft_count_size_ld_st(((t_compl*)tmp->content)->tkn, &tmp, &size);
		if (((t_compl*)tmp->content)->type == _SEP
				|| ((t_compl*)tmp->content)->type == _LAB)
			tmp = tmp->next;
	}
	return (size);
}

int			ft_count_size(t_list *list)
{
	int		size;

	if (!(size = ft_count_every_line(&list)))
		return (0);
	return (size);
}
