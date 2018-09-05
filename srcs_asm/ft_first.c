/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_first.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lotoussa <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/21 17:18:55 by lotoussa     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/05 13:18:25 by lotoussa    ###    #+. /#+    ###.fr     */
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
		ft_printf("Can't read source file %s\n", _ARG);
		return (NULL);
	}
	while (get_next_line(fd, &tmp))
	{
		if (!(file = ft_strfjoin(file, tmp)))
			exit(1);
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
		ft_printf("Usage: %s %s", argv[0], _USAGE);
		exit(1);
	}
	if (!(file = ft_read_file(argc, argv)))
		exit(1);
	return (file);
}
