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

char		*ft_lexer(char *file)
{
	t_contain	ctn;

	ctn.buf = ft_strdup("|");
	while (*file)
	{
		ctn.tkn = ft_strdup("|");
		while (ft_char(*file))
		{
			ctn.glu[0] = *file++;
			ctn.fre = ctn.tkn;
			if (!(ctn.tkn = ft_strjoin(ctn.tkn, ctn.glu)))
				return (NULL);
			free(ctn.fre);
		}
		if (!ft_strcmp(ctn.tkn, "|"))
		{
			ctn.fre = ctn.tkn;
			ctn.glu[0] = *file++;
			if (!(ctn.tkn = ft_strjoin(ctn.tkn, ctn.glu)))
				return (NULL);
			free(ctn.fre);
		}
		ft_fill_buf(&ctn.buf, &ctn.tkn);
	}
	return (ctn.buf);
}

int			ft_parsing(char *file)
{
	char	*buf;
	char	**split;

	if (!(buf = ft_lexer(file)))
	{
		free(file);
		exit(1);
	}
	split = ft_strsplit(buf, '|');
	free(buf);
	return (0);
}
