/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_third.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lotoussa <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/21 17:19:06 by lotoussa     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/27 21:48:57 by lotoussa    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/asm.h"
#include <fcntl.h>

static char		*ft_exit_third(char **file, char **tmp)
{
	if (*file)
		ft_strdel(file);
	if (*tmp)
		ft_strdel(tmp);
	return (NULL);
}

char			*ft_name_file(int argc, char **argv)
{
	int			f;
	char		*str;

	str = NULL;
	if (!ft_strcmp((_ARG + ft_strlen(_ARG) - 2), ".s"))
	{
		if (!(str = ft_arg(argc, argv)))
			return (ft_exit_third(&str, NULL));
		if (!(str = ft_strfjoin(str, ft_strdup(".cor"))))
			return (ft_exit_third(&str, NULL));
		if ((f = open(str, O_RDWR | O_CREAT | O_TRUNC,
						S_IRUSR | S_IWUSR) == -1))
			ft_exit_third(&str, NULL);
	}
	else
	{
		if ((f = open(".cor", O_RDWR | O_CREAT | O_TRUNC,
						S_IRUSR | S_IWUSR) == -1))
			return (ft_exit_third(&str, NULL));
	}
	close(f);
	return (str ? str : ft_strdup(".cor"));
}

void			ft_print_zero(int fd, int i)
{
	int		j;

	j = 0;
	while (j < i)
	{
		fd_printf("%c", fd, 0);
		j++;
	}
}

int				ft_header(char **file, t_all a)
{
	int		fd;

	if ((fd = open(*file, O_RDWR) == -1))
	{
		ft_strdel(file);
		return (0);
	}
	lseek(fd, 0, SEEK_SET);
	ft_print_zero(fd, 1);
	fd_printf("%c%c%c%s", fd, 0b11101010, 0b10000011, 0b11110011, a.base.name);
	ft_print_zero(fd, 128 - ft_strlen(a.base.name));
	if (!(ft_print_size(a.file_size, fd)))
		return (0);
	fd_printf("%s", fd, a.base.comment);
	ft_print_zero(fd, 2048 - ft_strlen(a.base.comment));
	close(fd);
	return (1);
}

int				ft_third(char **argv, int argc, t_all *a)
{
//	t_list	*tmp;

/*	tmp = a->t;
	while (tmp)
	{
		ft_printf("%d -> \"%s\"\n", ((t_compl*)tmp->content)->line, ((t_compl*)tmp->content)->tkn);
		tmp = tmp->next;
	}*/
	if (!(a->file_name = ft_name_file(argc, argv)))
		return (0);
	if (!(ft_header(&a->file_name, *a)))
		return (0);
	ft_printf("Writing output program to %s\n", a->file_name);
	return (1);
}
