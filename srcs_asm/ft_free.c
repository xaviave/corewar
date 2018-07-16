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

int			ft_free_base(t_base *base)
{
	if (base->name)
		free(base->name);
	if (base->comment)
		free(base->comment);
	if (base->label)
		ft_free_things(NULL, base->label);
	return (0);
}
