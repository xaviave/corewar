/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_write_details.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lotoussa <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/04 16:33:32 by lotoussa     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/05 16:38:54 by lotoussa    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/asm.h"

void		ft_memrev(char *ptr, size_t n)
{
	char	tmp;

	tmp = *ptr;
	*ptr = ptr[n - 1];
	ptr[n - 1] = tmp;
	if (n > 3)
		ft_memrev(ptr + 1, n - 2);
}

int			ft_arrange_live(int fd, t_list *tmp)
{
	int		d;

	d = ft_atoi(((t_compl*)tmp->content)->tkn + 1);
	ft_memrev((char*)&d, 4);
	write(fd, &d, 4);
	return (1);
}

t_list		*ft_live_exception(int fd, t_list *tmp)
{
	int		d;

	if (((t_compl*)tmp->content)->tkn[1] != ':')
	{
		if (!(ft_arrange_live(fd, tmp)))
			return (0);
	}
	else
	{
		d = ((t_compl*)tmp->content)->lab - ((t_compl*)tmp->content)->size;
		ft_memrev((char*)&d, 4);
		write(fd, &d, 4);
	}
	return (tmp->next);
}

t_list		*ft_exception(int fd, t_list *tmp)
{
	int		d;

	if (!ft_strcmp(((t_compl*)tmp->content)->tkn, "live"))
		return (ft_live_exception(fd, tmp->next));
	tmp = tmp->next;
	if (((t_compl*)tmp->content)->tkn[1] != ':')
	{
		d = ft_atoi(((t_compl*)tmp->content)->tkn + 1);
		ft_memrev((char*)&d, 2);
		write(fd, &d, 2);
	}
	else
	{
		d = ((t_compl*)tmp->content)->lab - ((t_compl*)tmp->content)->size;
		ft_memrev((char*)&d, 2);
		write(fd, &d, 2);
	}
	return (tmp->next);
}

int			ft_binary_to_hexa(int fd, char *s)
{
	int		num;
	int		decimal_val;
	int		base;
	int		rem;

	decimal_val = 0;
	base = 1;
	num = ft_atoi(s);
	while (num > 0)
	{
		rem = num % 10;
		decimal_val = decimal_val + rem * base;
		num = num / 10;
		base = base * 2;
	}
	return (fd_printf("%c", fd, decimal_val));
}

t_list		*ft_byte_read_par(int fd, t_list *tmp, t_list **list)
{
	int		oct;
	int		d;

	oct = (!ft_strcmp(((t_compl*)tmp->content)->tkn, "and")
			|| !ft_strcmp(((t_compl*)tmp->content)->tkn, "or")
			|| !ft_strcmp(((t_compl*)tmp->content)->tkn, "xor")
			|| !ft_strcmp(((t_compl*)tmp->content)->tkn, "ld")
			|| !ft_strcmp(((t_compl*)tmp->content)->tkn, "st")
			|| !ft_strcmp(((t_compl*)tmp->content)->tkn, "lld") ? 4 : 2);
	while ((tmp = tmp->next) && ((t_compl*)tmp->content)->type == _PAR)
	{
		if (((t_compl*)tmp->content)->par_type == _REG)
			fd_printf("%c", fd, ft_atoi(((t_compl*)tmp->content)->tkn + 1));
		else if (((t_compl*)tmp->content)->par_type == _DIR)
			ft_size_par_exception(fd, oct, tmp);
		else if (((t_compl*)tmp->content)->par_type == _IND)
		{
			d = ft_atoi(((t_compl*)tmp->content)->tkn);
			ft_memrev((char*)&d, 2);
			write(fd, &d, 2);
		}
	}
	return (tmp);
}
