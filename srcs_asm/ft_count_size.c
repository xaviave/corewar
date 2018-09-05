/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_count_size.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lotoussa <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/27 21:03:53 by lotoussa     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/05 19:20:08 by lotoussa    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/asm.h"

void		ft_ins_dont_move(char *tkn, t_list **tmp, int *size)
{
	t_list		*inc;

	inc = *tmp;
	if (!CMP(tkn, "aff") || !CMP(tkn, "lfork")
			|| !CMP(tkn, "fork") || !CMP(tkn, "zjmp"))
	{
		while (inc && CMP(((t_compl*)inc->content)->tkn, "\n"))
			inc = inc->next;
		*tmp = (inc->next ? inc->next : inc);
		*size += 3;
		if (((t_compl*)((t_list*)*tmp)->content)->size)
			*tmp = (*tmp)->next;
		((t_compl*)((t_list*)*tmp)->content)->size = *size;
	}
	else if (!CMP(tkn, "live") || !CMP(tkn, "add")
			|| !CMP(tkn, "sub"))
	{
		while (inc && CMP(((t_compl*)inc->content)->tkn, "\n"))
			inc = inc->next;
		*tmp = (inc->next ? inc->next : inc);
		*size += 5;
		if (((t_compl*)((t_list*)*tmp)->content)->size)
			*tmp = (*tmp)->next;
		((t_compl*)((t_list*)*tmp)->content)->size = *size;
	}
}

void		ft_ins_ott(char *tkn, t_list **tmp, int *size)
{
	t_list		*inc;

	inc = *tmp;
	if (!CMP(tkn, "ldi") || !CMP(tkn, "sti")
			|| !CMP(tkn, "lldi"))
	{
		*size += 2;
		while (inc && CMP(((t_compl*)inc->content)->tkn, "\n"))
		{
			if (((t_compl*)inc->content)->par_type == _REG)
				*size += 1;
			else if (((t_compl*)inc->content)->par_type == _DIR
					|| ((t_compl*)inc->content)->par_type == _IND)
				*size += 2;
			inc = inc->next;
		}
		if (((t_compl*)((t_list*)*tmp)->content)->size)
			*tmp = (*tmp)->next;
		((t_compl*)((t_list*)*tmp)->content)->size = *size;
		*tmp = (inc->next ? inc->next : inc);
	}
}

void		ft_ins_oft(char *tkn, t_list **tmp, int *size)
{
	t_list		*inc;

	inc = *tmp;
	if (!CMP(tkn, "and") || !CMP(tkn, "or")
			|| !CMP(tkn, "xor") || !CMP(tkn, "lld"))
	{
		*size += 2;
		while (inc && CMP(((t_compl*)inc->content)->tkn, "\n"))
		{
			if (((t_compl*)inc->content)->par_type == _REG)
				*size += 1;
			else if (((t_compl*)inc->content)->par_type == _DIR)
				*size += 4;
			else if (((t_compl*)inc->content)->par_type == _IND)
				*size += 2;
			inc = inc->next;
		}
		if (((t_compl*)((t_list*)*tmp)->content)->size)
			*tmp = (*tmp)->next;
		((t_compl*)((t_list*)*tmp)->content)->size = *size;
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
		if (((t_compl*)tmp->content)->type == _LAB)
			((t_compl*)tmp->content)->par_type = size;
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
