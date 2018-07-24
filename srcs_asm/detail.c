/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   detail.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lotoussa <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/23 16:24:43 by lotoussa     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/23 20:31:42 by lotoussa    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/asm.h"

int			ft_is_ins(t_list *tmp)
{
	char	*s;

	s = ((t_compl*)tmp->content)->tkn;
	return ((!ft_strcmp(s, "live") || !ft_strcmp(s, "ld") ||
				!ft_strcmp(s, "st") || !ft_strcmp(s, "add") ||
				!ft_strcmp(s, "sub") || !ft_strcmp(s, "and") ||
				!ft_strcmp(s, "or") || !ft_strcmp(s, "xor") ||
			!ft_strcmp(s, "zjmp") || !ft_strcmp(s, "ldi") ||
			!ft_strcmp(s, "sti") || !ft_strcmp(s, "fork") ||
			!ft_strcmp(s, "lld") || !ft_strcmp(s, "lldi") ||
			!ft_strcmp(s, "lfork") || !ft_strcmp(s, "aff")) ? 1 : 0);
}

int			ft_is_par(t_list *tmp)
{
	char	*s;
	int		i;

	s = ((t_compl*)tmp->content)->tkn;
	i = s[0] == '-' ? 1 : 0;
	if (s[0] == '%')
	{
		((t_compl*)tmp->content)->par_type = _DIR;
		return (1);
	}
	if (s[0] == 'r')
	{
		((t_compl*)tmp->content)->par_type = _REG;
		return (1);
	}
	if (s[0] == ':')
	{
		((t_compl*)tmp->content)->par_type = _IND;
		return (1);
	}
	if (!(ft_while_digit(s)))
		return (0);
	((t_compl*)tmp->content)->par_type = _IND;
	return (1);
}

int			ft_check_ins_alone(t_list **list)
{
	t_list		*tmp;

	tmp = *list;
	while (tmp)
	{
		if (((t_compl*)tmp->content)->type == _INS)
			if (!(ft_check_nb_ins_line(tmp, list)))
				return (0);
		tmp = tmp->next;
	}
	return (1);
}

int			ft_every_detail(t_list **list)
{
	t_list		*tmp;

	tmp = *list;
	while (tmp)
	{
		if (((t_compl*)tmp->content)->type == _LAB)
			if (!ft_check_label_char(((t_compl*)tmp->content)->tkn, tmp))
				return (0);
		tmp = tmp->next;
	}
	tmp = *list;
	while (tmp)
	{
		if (((t_compl*)tmp->content)->type == _PAR)
			if (!ft_check_par_alone(((t_compl*)tmp->content)->tkn, tmp, list))
				return (ft_printf("Error at PARAMETER \"%s\" line %d\n",
				((t_compl*)tmp->content)->tkn, ((t_compl*)tmp->content)->line));
		tmp = tmp->next;
	}
	if (!ft_check_ins_alone(list))
		return (0);
	return (768368);
}

int			ft_check_detail(t_list **list)
{
	t_list		*tmp;

	tmp = *list;
	while (tmp)
	{
		if (ft_is_ins(tmp))
			((t_compl*)tmp->content)->type = _INS;
		else if (((t_compl*)tmp->content)->\
				tkn[ft_strlen(((t_compl*)tmp->content)->tkn) - 1] == ':')
			((t_compl*)tmp->content)->type = _LAB;
		else if (ft_is_par(tmp))
			((t_compl*)tmp->content)->type = _PAR;
		else
			((t_compl*)tmp->content)->type = _SEP;
		tmp = tmp->next;
	}
	if (ft_every_detail(list) != 768368)
		return (0);
	return (1);
}
