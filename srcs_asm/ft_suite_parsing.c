#include "../includes/asm.h"

int			ft_check_base(char **ch)
{
	int		i;
	int		j;
	int		g[3];

	i = -1;
	ft_bzero(g, sizeof(g));
	while (ch[++i] && g[0] != 13 && g[1] != 13)
	{
		g[2] = 0;
		j = 0;
		if (ch[i][0] != '#' &&
				(ft_strstr(ch[i], ".name") || ft_strstr(ch[i], ".comment")))
		{
			while (ch[i][j])
				if (ch[i][j++] == '\"')
					g[2] = g[2] + 1;
			if (ch[i][1] == 'n')
				g[0] = (ch[i][0] == '.' && g[0] == 0 && g[2] == 2 ? 1 : 13);
			else
				g[1] = (ch[i][0] == '.' && g[1] == 0 && g[2] == 2 ? 1 : 13);
		}
	}
	return (g[0] == 1 && g[1] == 1 ? 1 : 0);
}

int			ft_count_base(char **ch)
{
	int		co;
	int		i;

	co = 0;
	i = 0;
	while (ch[i])
	{
		if (ch[i][0] == '.' && (ch[i][1] == 'n' || ch[i][1] == 'c') &&
				(ft_strstr(ch[i], ".name") || ft_strstr(ch[i], ".comment")))
			co++;
		i++;
	}
	return (co == 2 ? 1 : 0);
}

int			ft_create_base(char **sp, t_base *base, char **split)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (!ft_strstr(sp[i], ".name") || sp[i][0] != '.')
		i++;
	if (!(base->name = ft_extract_comment(sp[i])))
		return (0);
	while (!ft_strstr(sp[i], ".comment") || sp[i][0] != '.')
		i++;
	if (!(base->comment = ft_extract_comment(sp[i])))
		return (0);
	if (!(base->label = ft_extract_label(split)))
		return (0);
	return (1);
}

int			ft_start_base(char *file, char **split, t_base *base)
{
	char	**ch;
	int		i;

	if (!(ch = ft_strsplit(file, '\n')))
		return (0);
	i = 0;
	if (!(ft_count_base(ch)))
		return (ft_free_things(NULL, ch));
	if (!(ft_check_base(ch)))
		return (ft_free_things(NULL, ch));
	if (!(ft_create_base(ch, base, split)))
	{
		ft_free_base(base);
		return (ft_free_things(NULL, ch));
	}
	ft_free_things(NULL, ch);
	return (1);
}

int			ft_suite_parsing(char **file, char **split)
{
	t_base		base;

	if (!(ft_start_base(*file, split, &base)))
		return (0);
	return (1);
}
