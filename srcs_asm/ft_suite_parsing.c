/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_suite_parsing.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lotoussa <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/21 17:19:03 by lotoussa     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/23 14:57:57 by lotoussa    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/asm.h"

int			ft_is_valid_line_base(char *line)
{
	int		i;
	int		c;

	i = 0;
	c = 0;
	while (line[i] && c < 2)
	{
		if (line[i] == '\"')
			c++;
		i++;
	}
	if (line[i] != '\0')
	{
		ft_printf(ft_strstr(line, ".name") ?
				"Error at [.name] line\n" : "Error at [.comment] line\n");
		return (0);
	}
	return (1);
}

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
			if (!ft_is_valid_line_base(ch[i]))
				return (0);
		}
	}
	return (g[0] == 1 && g[1] == 1 ? 1 : 0);
}

int			ft_count_base(char **ch)
{
	int		co;
	int		i;
	int		l;

	co = 0;
	i = 0;
	l = -1;
	while (ch[i])
	{
		if (co < 2 && ch[i][0] != '#' && ch[i][0] != '.')
			l = i;
		if (ch[i][0] == '.' && (ch[i][1] == 'n' || ch[i][1] == 'c') &&
				(ft_strstr(ch[i], ".name") || ft_strstr(ch[i], ".comment")))
			co++;
		i++;
	}
	if (co != 2)
		ft_printf("[.name] or [.comment] have a duplicate line\n");
	else if (l != -1)
		ft_printf("Error at line %d\n", l + 1);
	return (co == 2 && l == -1 ? 1 : 0);
}

int			ft_create_base(char **sp, t_base *base, char **split)
{
	int		i;

	i = 0;
	while (!ft_strstr(sp[i], ".name") || sp[i][0] != '.')
		i++;
	if (!(base->name = ft_extract_comment(sp[i])))
		return (0);
	if (ft_strlen(base->name) > 128)
		return (ft_printf("Champion name too long (Max length 128)\n"));
	while (!ft_strstr(sp[i], ".comment") || sp[i][0] != '.')
		i++;
	if (!(base->comment = ft_extract_comment(sp[i])))
		return (0);
	if (ft_strlen(base->comment) > 2048)
		return (ft_printf("Champion comment too long (Max length 2048)\n"));
	return (1);
}

int			ft_suite_parsing(char **file, char **split, t_all *a)
{
	t_base	base;
	char	**ch;

	base.name = NULL;
	base.comment = NULL;
	if (!(ch = ft_strsplit(*file, '\n')))
		return (0);
	if (!(ft_count_base(ch)))
		return (ft_free_things(NULL, ch));
	if (!(ft_check_base(ch)))
		return (ft_free_things(NULL, ch));
	if ((ft_create_base(ch, &base, split) != 1))
	{
		ft_free_base(&base);
		return (ft_free_things(NULL, ch));
	}
	ft_free_things(NULL, ch);
	a->base = base;
	return (1);
}
