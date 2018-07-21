/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_third.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lotoussa <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/21 17:19:06 by lotoussa     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/21 19:23:48 by lotoussa    ###    #+. /#+    ###.fr     */
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
	int		fd;
	char	*file;
	char	*tmp;

	file = NULL;
	if (!ft_strcmp((_ARG + ft_strlen(_ARG) - 2), ".s"))
	{
		file = ft_memalloc(ft_strlen(_ARG) - 2);
		file = ft_strncpy(file, _ARG, ft_strlen(_ARG) - 2);
		tmp = file;
		if (!(file = ft_strjoin(file, ".cor")))
			ft_exit_third(&file, &tmp);
		free(tmp);
		if ((fd = open(file, O_RDWR | O_CREAT, S_IRUSR + S_IWUSR) == -1))
			ft_exit_third(&file, &tmp);
	}
	else
	{
		if ((fd = open(".cor", O_RDWR | O_CREAT, S_IRUSR + S_IWUSR) == -1))
			ft_exit_third(&file, &tmp);
	}
	close(fd);
	return (file ? file : ft_strdup(".cor"));
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
