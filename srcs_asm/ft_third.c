#include "../includes/asm.h"
#include <fcntl.h>

void			ft_errase(int *fd, char **name)
{
	*fd = open(*name, O_RDWR);
	lseek(*fd, 0, SEEK_SET);
	write(*fd, "a", 1);
}

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
		if ((fd = open(".cor", O_RDWR | O_CREAT, S_IRUSR + S_IWUSR) == -1))
			ft_exit_third(&file, &tmp);
	close(fd);
	return (file ? file : ".cor");
}

int				ft_third(char **argv, int argc)
{
	char	*file;

	file = ft_name_file(argc, argv);
	return (0);
}
