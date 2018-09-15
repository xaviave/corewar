/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   detail.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lotoussa <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/23 16:24:43 by lotoussa     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/12 20:20:26 by lotoussa    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/asm.h"

int			ft_is_ins(t_list *tmp)
{
	char	*s;

	s = ((t_compl*)tmp->content)->tkn;
	return ((!CMP(s, "live") || !CMP(s, "ld") ||
				!CMP(s, "st") || !CMP(s, "add") ||
				!CMP(s, "sub") || !CMP(s, "and") ||
				!CMP(s, "or") || !CMP(s, "xor") ||
				!CMP(s, "zjmp") || !CMP(s, "ldi") ||
				!CMP(s, "sti") || !CMP(s, "fork") ||
				!CMP(s, "lld") || !CMP(s, "lldi") ||
				!CMP(s, "lfork") || !CMP(s, "aff")) ? 1 : 0);
}

int			ft_is_par(t_list *tmp)
{
	char	*s;

	s = ((t_compl*)tmp->content)->tkn;
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
	if (!(ft_while_digit(s[0] == '-' ? s + 1 : s)))
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
			if (!ft_check_nb_ins_line(tmp, list) || !ft_check_nb_ins_par(tmp))
			{
				ft_putstr("Error at INSTRUCTION \"");
				ft_putstr(((t_compl*)tmp->content)->tkn);
				ft_putstr("\" line ");
				ft_putnbr(((t_compl*)tmp->content)->line);
				ft_putchar('\n');
				return (1);
			}
		tmp = tmp->next;
	}
	tmp = *list;
	while (tmp)
	{
		if (((t_compl*)tmp->content)->type == _INS)
			if (!ft_check_ins_type_par(tmp, ((t_compl*)tmp->content)->tkn))
			{
				ft_putstr("Error at INSTRUCTION \"");
				ft_putstr(((t_compl*)tmp->content)->tkn);
				ft_putstr("\" line ");
				ft_putnbr(((t_compl*)tmp->content)->line);
				ft_putchar('\n');
				return (1);
			}
		tmp = tmp->next;
	}
	return (768368);
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
			{
				ft_putstr("Error at PARAMETER \"");
				ft_putstr(((t_compl*)tmp->content)->tkn);
				ft_putstr("\" line ");
				ft_putnbr(((t_compl*)tmp->content)->line);
				ft_putchar('\n');
				return (1);
			}
		tmp = tmp->next;
	}
	if (ft_check_ins_alone(list) != 768368)
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
	if (!ft_bad_line(list))
		return (0);
	return (1);
}
