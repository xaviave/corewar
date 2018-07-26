#include "../includes/asm.h"

int			ft_anyway(t_all *a)
{
	int		i;
	char	*tmp;

	i = 0;
	while (a->base.tkn[i] && (!ft_strcmp(a->base.tkn[i], "#") || !ft_strcmp(a->\
					base.tkn[i], ".") || !ft_strcmp(a->base.tkn[i], "\n")))
	{
		while (a->base.tkn[i] && ft_strcmp(a->base.tkn[i], "\n"))
			i++;
		i++;
	}
	while (a->base.tkn[i])
	{
		if (!ft_strcmp(a->base.tkn[i], ";"))
		{
			tmp = a->base.tkn[i];
			a->base.tkn[i] = ft_strdup("#");
			free(tmp);
		}
		i++;
	}
	return (1);
}
