/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tools.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lotoussa <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/23 15:05:35 by lotoussa     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/05 19:21:04 by lotoussa    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/asm.h"

int			ft_while_digit(char *s)
{
	int		i;

	i = 0;
	while (s[i])
		if (!ft_isdigit(s[i++]))
			return (0);
	return (1);
}

int			ft_increment_tkn(char **tkn, int i, int *l)
{
	while (tkn[i] && CMP(tkn[i], "\n"))
		i++;
	if (!CMP(tkn[i], "\n"))
		(*l)++;
	i++;
	return (i);
}

int			ft_increment_tkn_second(char **tkn, int i, int *l)
{
	while (tkn[i] && CMP(tkn[i], "\n"))
		i++;
	if (!CMP(tkn[i], "\n"))
		(*l)++;
	return (i);
}

int			ft_associate_label(t_list *tmp, t_list *list)
{
	char	*dup;

	if (!(dup = ft_strfjoin(ft_strdup(((t_compl*)tmp->content)->tkn + 2),
					ft_strdup(":"))))
		return (0);
	while (list)
	{
		if (((t_compl*)list->content)->type == _LAB && !CMP(dup,
					((t_compl*)list->content)->tkn))
		{
			((t_compl*)tmp->content)->lab = ((t_compl*)list->content)->par_type;
			ft_strdel(&dup);
			return (1);
		}
		list = list->next;
	}
	ft_strdel(&dup);
	return (1);
}

int			ft_brut_label(t_all *a)
{
	t_list		*tmp;
	t_list		*list;

	tmp = a->t;
	while (tmp)
	{
		list = a->t;
		if (((t_compl*)tmp->content)->type == _PAR &&
				((t_compl*)tmp->content)->par_type == _DIR &&
				((t_compl*)tmp->content)->tkn[1] == ':')
			if (!(ft_associate_label(tmp, list)))
				return (0);
		tmp = tmp->next;
	}
	return (1);
}
