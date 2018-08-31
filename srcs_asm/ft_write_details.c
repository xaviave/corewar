#include "../includes/asm.h"

int			ft_binary_to_hexa(int fd, char *tp)
{
	char	*a;
	int		num;
	int		b;

	a = tp;
	num = 0;
	while (*a)
	{
		b = (*a == '1' ? 1 : 0);
		num = (num << 1) | b;
		a++;
	}
	return (fd_printf("%c\n", fd, num));
}

t_list		*ft_byte_read_par(int fd, t_list *tmp, t_list **list)
{
	tmp = tmp->next;
	while (tmp && ((t_compl*)tmp->content)->type == 3)
	{
		if (((t_compl*)tmp->content)->par_type == _REG)
			fd_printf("%c", fd, ft_atoi(((t_compl*)tmp->content)->tkn + 1));
		else if (((t_compl*)tmp->content)->par_type == _DIR)
			tmp = tmp;
			/* gerer les labels, transformer les _DIR en valeur puis en %c qui boucle pour 2 octets  */
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
