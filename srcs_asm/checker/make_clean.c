/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   make_clean.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xmoreau <xmoreau@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/24 18:29:00 by lotoussa     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/04 16:21:02 by xmoreau     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/asm.h"

static char				*join_split_file(char **s, int i)
{
	char	*join;
	char	*tmp;

	if (!(join = (!ft_strcmp(s[i], "\n") ?
					ft_strdup(s[i]) : ft_strjoin(s[i], "\n"))))
	{
		free_tab(s);
		return (NULL);
	}
	while (s[++i])
	{
		tmp = join;
		if (!(join = ft_strjoin(join, s[i])))
			return (NULL);
		ft_strdel(&tmp);
		if (ft_strcmp(s[i], "\n"))
		{
			tmp = join;
			if (!(join = ft_strjoin(join, "\n")))
				return (NULL);
			ft_strdel(&tmp);
		}
	}
	free_tab(s);
	return (join);
}

static char				*recreate_line(char *line)
{
	int		i;
	int		comment;

	i = 0;
	if (ft_strstr(line, NAME_CMD_STRING) || ft_strstr(line, COMMENT_CMD_STRING))
	{
		comment = 0;
		while (line[i])
		{
			if (line[i] == '"')
				comment = (comment == 0 ? 1 : 0);
			if ((line[i] == '#' || line[i] == ';') && comment == 0)
				return (ft_strsub(line, 0, i));
			i++;
		}
	}
	else
		while (line[i] && line[i] != '#' && line[i] != ';')
			i++;
	return (line[i] ? ft_strsub(line, 0, i) : ft_strdup(line));
}

static int				errase_empty_line(char **split)
{
	int		i;
	int		j;
	int		check;
	char	*tmp;

	i = 0;
	while (split[i])
	{
		j = 0;
		check = 0;
		while (split[i][j] && check == 0)
		{
			check = (split[i][j] != ' ' && split[i][j] != '\t' ? 1 : 0);
			j++;
		}
		if (check == 0)
		{
			tmp = split[i];
			if (!(split[i] = ft_strdup("\n")))
				return (0);
			ft_strdel(&tmp);
		}
		i++;
	}
	return (1);
}

static char				*errase_comment(char *file)
{
	char		**split;
	char		*tmp;
	int			i;

	if (!(split = ft_strsplit_modif(file, '\n')))
		return (NULL);
	i = -1;
	while (split[++i])
	{
		tmp = split[i];
		if (!(split[i] = recreate_line(split[i])))
		{
			ft_strdel(&tmp);
			return (NULL);
		}
		ft_strdel(&tmp);
	}
	if (!(errase_empty_line(split)))
		return (NULL);
	return (join_split_file(split, 0));
}

char					*make_clean(char *file)
{
	char	*tmp;
	char	*new_file;

	new_file = ft_strjoin(file, "\n");
	ft_strdel(&file);
	file = new_file;
	tmp = file;
	if ((file = errase_comment(file)) == NULL)
	{
		ft_strdel(&tmp);
		ft_printf("Can't work on source file\n");
		return (NULL);
	}
	ft_strdel(&tmp);
	return (file);
}
