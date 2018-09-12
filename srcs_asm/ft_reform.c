/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_reform.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lotoussa <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/04 16:35:52 by lotoussa     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/12 16:54:55 by xamartin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/asm.h"

int			ft_del_sep(t_list **list, int i, char *tkn)
{
	t_list		*tmp;
	t_list		*buf;

	tmp = *list;
	while (tmp && i && CMP(((t_compl*)tmp->next->content)->tkn, tkn))
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
	((t_compl*)buf->content)->lab = 0;
	((t_compl*)buf->content)->size = 0;
	free(((t_compl*)buf->content));
	free(buf);
	buf = NULL;
	return (1);
}

int			ft_del_sep_first_item(t_list **list)
{
	t_list		*tmp;
	t_list		*buf;

	tmp = *list;
	buf = (*list)->next;
	ft_strdel(&((t_compl*)tmp->content)->tkn);
	((t_compl*)tmp->content)->type = 0;
	((t_compl*)tmp->content)->par_type = 0;
	((t_compl*)tmp->content)->line = 0;
	((t_compl*)tmp->content)->lab = 0;
	((t_compl*)tmp->content)->size = 0;
	free(((t_compl*)tmp->content));
	free(tmp);
	tmp = NULL;
	*list = buf;
	return (1);
}

int			ft_reform(t_all *a)
{
	t_list		*tmp;
	int			i;

	tmp = a->t;
	i = 0;
	if (((t_compl*)tmp->content)->type == _SEP)
		ft_del_sep_first_item(&a->t);
	while (tmp)
	{
		if (((t_compl*)tmp->content)->type == _SEP)
			ft_del_sep(&a->t, i, ((t_compl*)tmp->content)->tkn);
		tmp = tmp->next;
		i++;
	}
	return (1);
}
