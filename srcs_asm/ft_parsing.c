/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_parsing.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lotoussa <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/21 16:42:25 by lotoussa     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/12 19:08:32 by xamartin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/asm.h"

int			ft_char(char let)
{
	return ((let == '.' || let == ' ' || let == '"' || let == '\n' || let == ','
				|| let == '\t' || let == '#' || let == ';') ? 0 : 1);
}

int			ft_fill_buf(char **buf, char **tkn)
{
	char	*tmp;

	tmp = *buf;
	if (!(*buf = ft_strjoin(*buf, *tkn)))
	{
		ft_strdel(&tmp);
		ft_strdel(tkn);
		return (0);
	}
	ft_strdel(&tmp);
	tmp = *buf;
	if (!(*buf = ft_strjoin(*buf, "|")))
	{
		ft_strdel(&tmp);
		ft_strdel(tkn);
		return (0);
	}
	ft_strdel(&tmp);
	ft_strdel(tkn);
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
		ft_strdel(&ctn->buf);
		ft_strdel(&ctn->fre);
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
			ft_strdel(&ctn.fre);
		}
		if (!CMP(ctn.tkn, "|"))
		{
			ctn.fre = ctn.tkn;
			if (!(ctn.tkn = ft_separator(&file, &ctn)))
				return (NULL);
			ft_strdel(&ctn.fre);
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

	split = NULL;
	if (!(buf = ft_lexer(*file)))
	{
		ft_strdel(file);
		exit(1);
	}
	if (!(split = ft_strsplit(buf, '|')))
	{
		ft_strdel(file);
		ft_strdel(&buf);
		exit(1);
	}
	ft_strdel(&buf);
	if (!(ft_suite_parsing(file, &a)))
	{
		ft_free_things(*file, split);
		exit(1);
	}
	ft_strdel(file);
	a.base.tkn = split;
	return (a);
}
