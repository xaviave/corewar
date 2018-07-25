/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_third.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lotoussa <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/21 17:19:06 by lotoussa     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/25 19:35:42 by lotoussa    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/asm.h"
#include <fcntl.h>

static void		ft_exit_third(char **file, char **tmp)
{
	if (*file)
		free(*file);
	if (*tmp)
		free(*tmp);
	exit(1);
}

char			*ft_name_file(int argc, char **argv)
{
	int			f;
	t_contain	c;

	c.tkn = NULL;
	if (!ft_strcmp((_ARG + ft_strlen(_ARG) - 2), ".s"))
	{
		c.buf = ft_strdup(_ARG);
		c.tkn = ft_strndup(c.buf, ft_strlen(c.buf) - 2);
		ft_strdel(&c.buf);
		c.fre = c.tkn;
		if (!(c.tkn = ft_strjoin(c.tkn, ".cor")))
			ft_exit_third(&c.tkn, &c.fre);
		ft_strdel(&c.fre);
		if ((f = open(c.tkn, O_RDWR | O_CREAT | O_TRUNC,
						S_IRUSR | S_IWUSR) == -1))
			ft_exit_third(&c.tkn, &c.fre);
	}
	else
	{
		if ((f = open(".cor", O_RDWR | O_CREAT | O_TRUNC,
						S_IRUSR | S_IWUSR) == -1))
			ft_exit_third(&c.tkn, &c.fre);
	}
	close(f);
	return (c.tkn ? c.tkn : ft_strdup(".cor"));
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
		free(*file);
		exit(1);
	}
	lseek(fd, 0, SEEK_SET);
	ft_print_zero(fd, 1);
	fd_printf("%c%c%c%s", fd, 0b11101010, 0b10000011, 0b11110011, a.base.name);
	ft_print_zero(fd, 128 - ft_strlen(a.base.name));
	/* file size */ ft_print_zero(fd, 8);
	fd_printf("%s", fd, a.base.comment);
	ft_print_zero(fd, 2048 - ft_strlen(a.base.comment));
	close(fd);
	return (0);
}

int				ft_third(char **argv, int argc, t_all *a)
{
	a->file_name = ft_name_file(argc, argv);
	ft_header(&a->file_name, *a);
	ft_printf("Writing output program to %s\n", a->file_name);
	return (0);
}
