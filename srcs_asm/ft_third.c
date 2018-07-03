#include "../includes/asm.h"
#include <fcntl.h>

void			ft_name_file(int argc, char **argv, int *fd)
{
	char	*name;
	char	*tmp;

	if (!(name = ft_strndup(argv[argc - 1], ft_strlen(argv[argc - 1]))))
		exit(1);
	if (name[ft_strlen(name) - 2] == '.' && name[ft_strlen(name) - 1] == 's')
		{
			tmp = name;
			name = ft_strjoin(ft_strndup(name, ft_strlen(name) - 2), ".cor");
			free(tmp);
			if ((*fd = open(name, O_CREAT) == -1))
				exit(1);
		}
	else
	{
		if ((*fd = open(".cor", O_CREAT) == -1))
		{
			free(name);
			exit(1);
		}
	}
	free(name);
}

int				ft_third(char **argv, int argc)
{
	int		fd;

	ft_name_file(argc, argv, &fd);
	close(fd);
	return (0);
}
