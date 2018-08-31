#include "../includes/asm.h"

int		ft_binary_to_hexa(int fd, char *s)
{
	char	c;
	int		i;
	char	temp;

	c = 0;
	i = 0;
	temp = 0;
	while (i < 8)
	{
		if (s[i] == '1')
			temp = 1;
		temp = temp << (7 - i);
		c = c | temp;
		i++;
	}
	return (ft_printf("%c", fd, c));
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
			if (ft_strlen(pf_litoa_base(((t_compl*)tmp->content)->lab,
							"0123456789")) < 4)
				fd_printf("%c", fd, 0);
			fd_printf("%c", fd, ((t_compl*)tmp->content)->lab);
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
