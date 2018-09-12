/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_first.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lotoussa <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/21 17:18:55 by lotoussa     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/12 20:01:57 by lotoussa    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/asm.h"
#include <fcntl.h>

char			*ft_read_file(int argc, char **argv)
{
	char	*file;
	char	*tmp;
	int		fd;

	file = NULL;
	if ((fd = open(_ARG, O_RDONLY)) == -1)
	{
		ft_putstr("Can't read source file ");
		ft_putendl(_ARG);
		return (NULL);
	}
	while (get_next_line(fd, &tmp))
	{
		if (!(file = ft_strfjoin(file, tmp)))
		{
			if (file)
				ft_strdel(&file);
			exit(1);
		}
		if (!(file = ft_strfjoin(file, ft_strdup("\n"))))
			exit(1);
	}
	close(fd);
	return (file);
}

char			*ft_first(int argc, char **argv)
{
	char	*file;

	file = NULL;
	if (argc < 2)
	{
		ft_putstr("Usage: ");
		ft_putstr(argv[0]);
		ft_putchar(' ');
		ft_putstr(_USAGE);
		exit(1);
	}
	if (!(file = ft_read_file(argc, argv)))
		exit(1);
	return (file);
}
