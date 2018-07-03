#include "../includes/asm.h"
#include <fcntl.h>

static void		ft_exit_error_local(char **file, char **tmp)
{
	free(*file);
	free(*tmp);
	exit(1);
}

int				ft_read_file(int argc, char **argv, char **file)
{
	char	*tmp;
	int		fd;

	if ((fd = open(argv[argc - 1], O_RDONLY)) == -1)
		return (ft_printf("Can't read source file %s\n", argv[argc - 1]));
	*file = ft_memalloc(0);
	while (get_next_line(fd, &tmp))
	{
		if (!(*file = ft_strjoin(*file, tmp)))
			ft_exit_error_local(file, &tmp);
		free(tmp);
		tmp = *file;
		if (!(*file = ft_strjoin(*file, "\n")))
			ft_exit_error_local(file, &tmp);
		free(tmp);
	}
	close(fd);
	return (0);
}

int				ft_first(int argc, char **argv, char **file)
{
	if (argc < 2)
	{
		ft_printf("Usage: %s %s", argv[0], _USAGE);
		exit(1);
	}
	if (ft_read_file(argc, argv, file))
		exit(1);
	return (0);
}
