#include "../includes/asm.h"
#include <fcntl.h>

static void		ft_exit_error_local(char **file, char **tmp)
{
	free(*file);
	free(*tmp);
	exit(1);
}

char			*ft_read_file(int argc, char **argv)
{
	char	*file;
	char	*tmp;
	char	*fre;
	int		fd;

	if ((fd = open(_ARG, O_RDONLY)) == -1)
	{
		ft_printf("Can't read source file %s\n", _ARG);
		return (NULL);
	}
	file = ft_memalloc(0);
	while (get_next_line(fd, &tmp))
	{
		fre = file;
		if (!(file = ft_strjoin(file, tmp)))
			ft_exit_error_local(&file, &tmp);
		free(fre);
		free(tmp);
		tmp = file;
		if (!(file = ft_strjoin(file, "\n")))
			ft_exit_error_local(&file, &tmp);
		free(tmp);
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
