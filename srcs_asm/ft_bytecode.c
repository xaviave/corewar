/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_bytecode.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lotoussa <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/04 16:37:26 by lotoussa     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/12 19:16:23 by xamartin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/asm.h"

int			ft_byte_read_ins_second(int fd, t_list *tmp)
{
	if (!(CMP(((t_compl*)tmp->content)->tkn, "sti")))
		ft_putchar_fd(11, fd);
	else if (!(CMP(((t_compl*)tmp->content)->tkn, "fork")))
		ft_putchar_fd(12, fd);
	else if (!(CMP(((t_compl*)tmp->content)->tkn, "lld")))
		ft_putchar_fd(13, fd);
	else if (!(CMP(((t_compl*)tmp->content)->tkn, "lldi")))
		ft_putchar_fd(14, fd);
	else if (!(CMP(((t_compl*)tmp->content)->tkn, "lfork")))
		ft_putchar_fd(15, fd);
	else if (!(CMP(((t_compl*)tmp->content)->tkn, "aff")))
		ft_putchar_fd(16, fd);
	return (1);
}

int			ft_byte_read_ins(int fd, t_list *tmp)
{
	if (!(CMP(((t_compl*)tmp->content)->tkn, "live")))
		ft_putchar_fd(1, fd);
	else if (!(CMP(((t_compl*)tmp->content)->tkn, "ld")))
		ft_putchar_fd(2, fd);
	else if (!(CMP(((t_compl*)tmp->content)->tkn, "st")))
		ft_putchar_fd(3, fd);
	else if (!(CMP(((t_compl*)tmp->content)->tkn, "add")))
		ft_putchar_fd(4, fd);
	else if (!(CMP(((t_compl*)tmp->content)->tkn, "sub")))
		ft_putchar_fd(5, fd);
	else if (!(CMP(((t_compl*)tmp->content)->tkn, "and")))
		ft_putchar_fd(6, fd);
	else if (!(CMP(((t_compl*)tmp->content)->tkn, "or")))
		ft_putchar_fd(7, fd);
	else if (!(CMP(((t_compl*)tmp->content)->tkn, "xor")))
		ft_putchar_fd(8, fd);
	else if (!(CMP(((t_compl*)tmp->content)->tkn, "zjmp")))
		ft_putchar_fd(9, fd);
	else if (!(CMP(((t_compl*)tmp->content)->tkn, "ldi")))
		ft_putchar_fd(10, fd);
	return (ft_byte_read_ins_second(fd, tmp));
}

int			ft_byte_read_type_par(int fd, t_list *list)
{
	int		i;
	char	*tp;

	i = 0;
	tp = ft_strdup(">");
	while ((list = list->next) && ((t_compl*)list->content)->type == 3)
	{
		if (((t_compl*)list->content)->par_type == _REG)
			tp = ft_strfjoin(tp, ft_strdup("01"));
		else if (((t_compl*)list->content)->par_type == _DIR)
			tp = ft_strfjoin(tp, ft_strdup("10"));
		else if (((t_compl*)list->content)->par_type == _IND)
			if (!(tp = ft_strfjoin(tp, ft_strdup("11"))))
				return (0);
	}
	while (ft_strlen(tp) < 8)
		if (!(tp = ft_strfjoin(tp, ft_strdup("00"))))
			return (0);
	if (!(ft_binary_to_hexa(fd, tp + 1)))
		return (0);
	ft_strdel(&tp);
	return (1);
}

int			ft_bc(int fd, t_list **list)
{
	t_list		*tmp;

	tmp = *list;
	while (tmp)
		if (((t_compl*)tmp->content)->type == _INS)
		{
			if (!(ft_byte_read_ins(fd, tmp)))
				return (0);
			if (CMP(((t_compl*)tmp->content)->tkn, "live") &&
					CMP(((t_compl*)tmp->content)->tkn, "zjmp") &&
					CMP(((t_compl*)tmp->content)->tkn, "fork") &&
					CMP(((t_compl*)tmp->content)->tkn, "lfork"))
				if (!(ft_byte_read_type_par(fd, tmp)))
					return (0);
			if (CMP(((t_compl*)tmp->content)->tkn, "live") &&
					CMP(((t_compl*)tmp->content)->tkn, "zjmp") &&
					CMP(((t_compl*)tmp->content)->tkn, "fork") &&
					CMP(((t_compl*)tmp->content)->tkn, "lfork"))
				tmp = ft_byte_read_par(fd, tmp);
			else
				tmp = ft_exception(fd, tmp);
		}
		else
			tmp = tmp->next;
	return (1);
}

int			ft_bytecode(int fd, t_all *a)
{
	t_list		*tmp;

	tmp = a->t;
	if (!(ft_create_size_tab(&tmp)))
		return (0);
	if (!(ft_attribute_last_lab(&tmp)))
		return (0);
	if (!(ft_bc(fd, &tmp)))
		return (0);
	return (1);
}
