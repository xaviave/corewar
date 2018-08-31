#include "../includes/asm.h"

t_list		*ft_live_exception(int fd, t_list *tmp)
{
	/* faire la meme chose pour live et rajouter le bon nombre doctet null */
	return (tmp->next);
}

t_list		*ft_exception(int fd, t_list *tmp)
{
	char	*dup;

	if (!ft_strcmp(((t_compl*)tmp->content)->tkn, "live"))
		return (ft_live_exception(fd, tmp->next));
	tmp = tmp->next;
	if (((t_compl*)tmp->content)->tkn[1] != ':')
	{
		dup = pf_litoa_base(ft_atoi(((t_compl*)tmp->content)->tkn + 1),
				"0123456789abcdef");
		if (ft_strlen(dup) < 4)
			fd_printf("%c", fd, 0);
		fd_printf("%c", fd, ft_atoi(((t_compl*)tmp->content)->tkn + 1));
		ft_strdel(&dup);
	}
	else
	{
		dup = pf_litoa_base(((t_compl*)tmp->content)->lab, "0123456789abcdef");
		if (ft_strlen(dup) < 4)
			fd_printf("%c", fd, 0);
		fd_printf("%c", fd, (((t_compl*)tmp->content)->lab)); /* verifier valeur label */
		ft_strdel(&dup);
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
		num = num / 10 ;
		base = base * 2;
	}
	ft_printf("%d\n", decimal_val);
	return (ft_printf("%c", fd, decimal_val));
}

t_list		*ft_byte_read_par(int fd, t_list *tmp, t_list **list)
{
	tmp = tmp->next;
	while (tmp && ((t_compl*)tmp->content)->type == 3)
	{
		if (((t_compl*)tmp->content)->par_type == _REG)
			fd_printf("%c", fd, ft_atoi(((t_compl*)tmp->content)->tkn + 1));
		else if (((t_compl*)tmp->content)->par_type == _DIR)
		{
			if (((t_compl*)tmp->content)->tkn[1] == ':')
			{
				if (ft_strlen(pf_litoa_base(((t_compl*)tmp->content)->lab,
								"0123456789")) < 4)
					fd_printf("%c", fd, 0);
				fd_printf("%c", fd, ((t_compl*)tmp->content)->lab);
			}
			else
			{
				((t_compl*)tmp->content)->lab =
					ft_atoi(((t_compl*)tmp->content)->tkn + 1);
				if (ft_strlen(((t_compl*)tmp->content)->tkn) - 1 < 4)
					fd_printf("%c", fd, 0);
				fd_printf("%c", fd, ((t_compl*)tmp->content)->lab);
			}
		}
		else if (((t_compl*)tmp->content)->par_type == _IND)
		{
			if (ft_strlen(((t_compl*)tmp->content)->tkn) < 4)
				fd_printf("%c", fd, 0);
			fd_printf("%c", fd, ft_atoi(((t_compl*)tmp->content)->tkn));
		}
		tmp = tmp->next;
	}
	return (tmp);
}
