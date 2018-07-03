#include "../includes/asm.h"

int			ft_first(int argc, char **argv)
{
	if (argc < 2)
	{
		ft_printf("Usage: %s %s", argv[0], _USAGE);
		exit(1);
	}
	return (0);
}
