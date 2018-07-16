#include "../includes/asm.h"

int			ft_char(char let)
{
	return ((let == '.' || let == ' ' || let == '"' || let == '\n' || let == ','
				|| let == '\t') ? 0 : 1);
}

int			ft_fill_buf(char **buf, char **tkn)
{
	char	*tmp;

	tmp = *buf;
	*buf = ft_strjoin(*buf, *tkn);
	free(tmp);
	tmp = *buf;
	*buf = ft_strjoin(*buf, "|");
	free(tmp);
	free(*tkn);
	return (1);
}

char		*ft_separator(char **file, char **tkn)
{
	char	glu[2];

	glu[0] = *(*file)++;
	glu[1] = '\0';
	return ((!(*tkn = ft_strjoin(*tkn, glu))) ? NULL : *tkn);
}

char		*ft_lexer(char *file)
{
	t_contain	ctn;

	ctn.buf = ft_strdup("|");
	while (*file)
	{
		ctn.tkn = ft_strdup("|");
		while (ft_char(*file))
		{
			ctn.fre = ctn.tkn;
			if (!(ctn.tkn = ft_separator(&file, &ctn.tkn)))
				return (NULL);
			free(ctn.fre);
		}
		if (!ft_strcmp(ctn.tkn, "|"))
		{
			ctn.fre = ctn.tkn;
			if (!(ctn.tkn = ft_separator(&file, &ctn.tkn)))
				return (NULL);
			free(ctn.fre);
		}
		ft_fill_buf(&ctn.buf, &ctn.tkn);
	}
	return (ctn.buf);
}

int			ft_parsing(char **file, t_all *a)
{
	char	*buf;
	char	**split;
	int		i;

	if (!(i = 0) && !(buf = ft_lexer(*file)))
	{
		free(*file);
		exit(1);
	}
	if (!(split = ft_strsplit(buf, '|')))
	{
		free(*file);
		free(buf);
		exit(1);
	}
	free(buf);
	if (!(a->base = ft_suite_parsing(file, split)))
	{
		ft_free_things(*file, split);
		exit(1);
	}
	ft_free_things(*file, split);
	return (1);
}
