/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_parsing.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lotoussa <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/21 16:42:25 by lotoussa     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/21 19:12:17 by lotoussa    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

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
	if (!(*buf = ft_strjoin(*buf, *tkn)))
	{
		free(tmp);
		free(*tkn);
		return (0);
	}
	free(tmp);
	tmp = *buf;
	if (!(*buf = ft_strjoin(*buf, "|")))
	{
		free(tmp);
		free(*tkn);
		return (0);
	}
	free(tmp);
	free(*tkn);
	return (1);
}

char		*ft_separator(char **file, t_contain *ctn)
{
	char	glu[2];
	int		ret;

	glu[0] = *(*file)++;
	glu[1] = '\0';
	if (!(ctn->tkn = ft_strjoin(ctn->tkn, glu)))
		ret = 0;
	else
		ret = 1;
	if (ret == 0)
	{
		free(ctn->buf);
		free(ctn->fre);
	}
	return (ret ? ctn->tkn : NULL);
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
			if (!(ctn.tkn = ft_separator(&file, &ctn)))
				return (NULL);
			free(ctn.fre);
		}
		if (!ft_strcmp(ctn.tkn, "|"))
		{
			ctn.fre = ctn.tkn;
			if (!(ctn.tkn = ft_separator(&file, &ctn)))
				return (NULL);
			free(ctn.fre);
		}
		if (!(ft_fill_buf(&ctn.buf, &ctn.tkn)))
			return (NULL);
	}
	return (ctn.buf);
}

t_all		ft_parsing(char **file)
{
	char	*buf;
	char	**split;
	t_all	a;

	if (!(buf = ft_lexer(*file)))
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
	if (!(ft_suite_parsing(file, split, &a)))
	{
		ft_free_things(*file, split);
		exit(1);
	}
	ft_free_things(*file, split);
	return (a);
}
