#include "../includes/asm.h"
#include <fcntl.h>

void			ft_errase(int *fd, char **name)
{
	*fd = open(*name, O_RDWR);
	lseek(*fd, 0, SEEK_SET);
	write(*fd, "a", 1);
}

static void		ft_exit_third(char **name, int *fd)
{
	free(*name);
	close(*fd);
	exit(1);
}

void			ft_name_file(int argc, char **argv, int *fd)
{
	char	*name;
	char	*tmp;

	if (!(name = ft_strdup(argv[argc - 1])))
		exit(1);
	if (!ft_strcmp((name + ft_strlen(name) - 2), ".s"))
	{
		name = realloc(name, ft_strlen(name) - 2);
		tmp = name;
		ft_printf("%s\n", name);
		name = ft_strjoin(name, ".cor");
		free(tmp);
		ft_printf("%s\n", name);
		if ((*fd = open(name, O_RDWR | O_CREAT, S_IRUSR + S_IWUSR) == -1))
			ft_exit_third(&name, fd);
	}
	else
		if ((*fd = open(".cor", O_RDWR | O_CREAT, S_IRUSR + S_IWUSR) == -1))
			ft_exit_third(&name, fd);
	ft_printf("name = %s\n/", name);
}

int				ft_third(char **argv, int argc)
{
	int		fd;

	ft_name_file(argc, argv, &fd);
	close(fd);
	return (0);
}
