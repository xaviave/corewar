#include "../includes/asm.h"

int			ft_free_things(char *s1, char **s2)
{
	int		i;

	i = 0;
	if (s1)
		free(s1);
	if (s2)
	{
		while (s2[i])
			free(s2[i++]);
		free(s2);
	}
	return (0);
}
