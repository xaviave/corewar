#include "../includes/asm.h"

int			ft_byte_read_ins_second(int fd, t_list *tmp)
{
	if (!(ft_strcmp(((t_compl*)tmp->content)->tkn, "sti")))
		return (fd_printf("%c", fd, 11));
	else if (!(ft_strcmp(((t_compl*)tmp->content)->tkn, "fork")))
		return (fd_printf("%c", fd, 12));
	else if (!(ft_strcmp(((t_compl*)tmp->content)->tkn, "lld")))
		return (fd_printf("%c", fd, 13));
	else if (!(ft_strcmp(((t_compl*)tmp->content)->tkn, "lldi")))
		return (fd_printf("%c", fd, 14));
	else if (!(ft_strcmp(((t_compl*)tmp->content)->tkn, "lfork")))
		return (fd_printf("%c", fd, 15));
	else if (!(ft_strcmp(((t_compl*)tmp->content)->tkn, "aff")))
		return (fd_printf("%c", fd, 16));
	return (1);
}

int			ft_byte_read_ins(int fd, t_list *tmp)
{
	if (!(ft_strcmp(((t_compl*)tmp->content)->tkn, "live")))
		return (fd_printf("%c", fd, 1));
	else if (!(ft_strcmp(((t_compl*)tmp->content)->tkn, "ld")))
		return (fd_printf("%c", fd, 2));
	else if (!(ft_strcmp(((t_compl*)tmp->content)->tkn, "st")))
		return (fd_printf("%c", fd, 3));
	else if (!(ft_strcmp(((t_compl*)tmp->content)->tkn, "add")))
		return (fd_printf("%c", fd, 4));
	else if (!(ft_strcmp(((t_compl*)tmp->content)->tkn, "sub")))
		return (fd_printf("%c", fd, 5));
	else if (!(ft_strcmp(((t_compl*)tmp->content)->tkn, "and")))
		return (fd_printf("%c", fd, 6));
	else if (!(ft_strcmp(((t_compl*)tmp->content)->tkn, "or")))
		return (fd_printf("%c", fd, 7));
	else if (!(ft_strcmp(((t_compl*)tmp->content)->tkn, "xor")))
		return (fd_printf("%c", fd, 8));
	else if (!(ft_strcmp(((t_compl*)tmp->content)->tkn, "zjmp")))
		return (fd_printf("%c", fd, 9));
	else if (!(ft_strcmp(((t_compl*)tmp->content)->tkn, "ldi")))
		return (fd_printf("%c", fd, 10));
	return (ft_byte_read_ins_second(fd, tmp));
}

int			ft_byte_read_type_par(int fd, t_list **list)
{
	char	*tp;
	int		i;

	/* tout faux, faire traduction -> sommes type par = binaire -> hexa */
	*list = (*list)->next;
	i = 0;
	while (((t_compl*)((t_list*)list)->content)->type != 2)
	{
		if (!(tp = ft_memalloc(4)))
			return (0);
		if (((t_compl*)((t_list*)list)->content)->par_type == _REG)
			tp[i] = 1;
		else if (((t_compl*)((t_list*)list)->content)->par_type == _DIR)
			tp[i] = 10;
		else if (((t_compl*)((t_list*)list)->content)->par_type == _IND)
			tp[i] = 11;
		*list = (*list)->next;
		i++;
	}
	fd_printf("%s", fd, tp);
	return (1);
}

int			ft_bc(int fd, t_list **list)
{
	t_list		*tmp;

	tmp = *list;
	while (tmp)
	{
		ft_printf("%s\n", ((t_compl*)tmp->content)->tkn);
		if (((t_compl*)tmp->content)->type == 2)
		{
			if (!(ft_byte_read_ins(fd, tmp)))
				return (0);
			if (!(ft_byte_read_type_par(fd, &tmp)))
				return (0);
		}
		else
			tmp = tmp->next;
	}
	return (1);
}

int			ft_bytecode(int fd, t_all *a)
{
	t_list		*tmp;

	tmp = a->t;
	if (!(ft_bc(fd, &tmp)))
		return (0);
	return (1);
}
