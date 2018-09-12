/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_write_details.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lotoussa <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/04 16:33:32 by lotoussa     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/12 17:33:52 by xamartin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/asm.h"

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

	if (!CMP(((t_compl*)tmp->content)->tkn, "live"))
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
	write(fd, &decimal_val, 1);
	return (1);
}

t_list		*ft_byte_read_par(int fd, t_list *tmp)
{
	char	*tkn;
	int		oct;
	int		d;

	tkn = ((t_compl*)tmp->content)->tkn;
	oct = (!CMP(tkn, "and") || !CMP(tkn, "or") || !CMP(tkn, "xor")
			|| !CMP(tkn, "ld") || !CMP(tkn, "st") || !CMP(tkn, "lld") ? 4 : 2);
	while ((tmp = tmp->next) && ((t_compl*)tmp->content)->type == _PAR)
	{
		if (((t_compl*)tmp->content)->par_type == _REG)
			fd_printf("%c", fd, ft_atoi(((t_compl*)tmp->content)->tkn + 1));
		else if (((t_compl*)tmp->content)->par_type == _DIR)
			ft_size_par_exception(fd, oct, tmp);
		else if (((t_compl*)tmp->content)->par_type == _IND)
		{
			d = (((t_compl*)tmp->content)->tkn[0] == ':' ? ((t_compl*)tmp->\
						content)->lab : ft_atoi(((t_compl*)tmp->content)->tkn));
			ft_memrev((char*)&d, 2);
			write(fd, &d, 2);
		}
	}
	return (tmp);
}
