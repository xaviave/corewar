#include "../includes/asm.h"

int			ft_size_base(char **tkn, int j)
{
	int		i;
	int		plus_size;

	i = 0;
	plus_size = 0;
	while (tkn[i])
	{
		if (i > j)
			if (!ft_strcmp(tkn[i], "#"))
				plus_size += 1;
		i++;
	}
	return (i + plus_size);
}

int			ft_recreate_base(t_all *a, int j)
{
	char	**rec;
	int		i;
	int		k;

	i = 0;
	k = 0;
	if (!(rec = ft_memalloc(ft_size_base(a->base.tkn, j))))
		return (0);
	while (a->base.tkn[i])
	{
		if (!ft_strcmp(a->base.tkn[i], "#") && i > j)
			if (!(rec[k++] = ft_strdup(" ")))
				return (0);
		if (!(rec[k++] = ft_strdup(a->base.tkn[i++])))
			return (0);
	}
	rec[k] = NULL;
	i = 0;
	while (a->base.tkn[i])
		ft_strdel(&a->base.tkn[i++]);
	free(a->base.tkn);
	a->base.tkn = rec;
	return (1);
}

int			ft_anyway(t_all *a)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (a->base.tkn[i] && (!ft_strcmp(a->base.tkn[i], "#") || !ft_strcmp(a->\
					base.tkn[i], ".") || !ft_strcmp(a->base.tkn[i], "\n")))
	{
		while (a->base.tkn[i] && ft_strcmp(a->base.tkn[i], "\n"))
			i++;
		i++;
	}
	j = i;
	while (a->base.tkn[i])
	{
		if (!ft_strcmp(a->base.tkn[i], ";"))
		{
			tmp = a->base.tkn[i];
			if (!(a->base.tkn[i] = ft_strdup("#")))
				return (0);
			ft_strdel(&tmp);
		}
		i++;
	}
	return (ft_recreate_base(a, j));
}
