/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check_name_comment.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xmoreau <xmoreau@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/01 13:14:21 by xmoreau      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/04 16:48:59 by xmoreau     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/asm.h"

static	int	count_quote_end(char *start)
{
	int		i;
	int		quote;
	int		backn;

	i = 0;
	quote = 0;
	backn = 0;
	while (start[i])
	{
		if (start[i] == '"')
			quote++;
		if (quote >= 2 && start[i] == '\n')
			backn++;
		if (quote >= 2 && ft_isalnum(start[i]) && backn == 0)
			return (0);
		i++;
	}
	if (quote != 2)
		return (0);
	return (1);
}

static	int	count_quote_len(int len, char *start)
{
	int		i;
	int		quote;

	i = 0;
	quote = 0;
	while (i < len)
	{
		if (start[i] == '"')
			quote++;
		if (quote >= 2 && ft_isalnum(start[i]))
			return (0);
		i++;
	}
	if (quote != 2)
		return (0);
	return (1);
}

int			check_for_quote(char *file)
{
	char	*name;
	char	*comment;
	int		len;
	int		end;

	len = 0;
	end = 0;
	name = ft_strstr(file, NAME_CMD_STRING);
	comment = ft_strstr(file, COMMENT_CMD_STRING);
	if (name < comment)
	{
		len = count_quote_len((int)(comment - name), name);
		end = count_quote_end(comment);
	}
	else
	{
		len = count_quote_len((int)(name - comment), comment);
		end = count_quote_end(name);
	}
	return (len & end);
}

static	int	add_to_control(t_control *control, int i, int n)
{
	if (n == 1)
	{
		if (control->name == 0)
			control->name = i + 1;
		else
			return (-2);
	}
	if (n == 2)
	{
		if (control->comment == 0)
			control->comment = i + 1;
		else
			return (-2);
	}
	return (1);
}

int			check_name_comment(char **tab, t_control *control)
{
	int		i;
	char	**line;
	int		ret;
	int		ret2;

	i = 0;
	line = NULL;
	ret = 0;
	ret2 = 0;
	while (tab[i])
	{
		line = multi_split(tab[i], SPLIT);
		if (ft_strequ(line[0], NAME_CMD_STRING) && line[1] != NULL)
			ret = add_to_control(control, i, 1);
		if (ft_strequ(line[0], COMMENT_CMD_STRING) && line[1] != NULL)
			ret2 = add_to_control(control, i, 2);
		if (ret == -2 || ret2 == -2)
		{
			free_tab(line);
			return (ret);
		}
		free_tab(line);
		i++;
	}
	return (1);
}
