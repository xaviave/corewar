/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check_line_composition.c                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xmoreau <xmoreau@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/01 18:12:23 by lotoussa     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/04 12:54:29 by xmoreau     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/asm.h"

static int		error_line_composition(char **split, int err, int i)
{
	int			ret;

	ret = -2;
	if (err == -1)
		ret = -1;
	if (err == -3)
		ft_printf("the instruction on line %s is incorrect\n", split[i]);
	if (err == -4)
	{
		ft_printf("the number of parametter on line ");
		ft_printf("%s is incorrect\n", split[i]);
	}
	if (err == -5)
		ft_printf("error with token ' , ' on line %s\n", split[i]);
	free_tab(split);
	return (ret);
}

static	char	**create_tab(char *file)
{
	char		**tab;
	char		*start;
	int			i;

	start = ft_strstr(file, COMMENT_CMD_STRING);
	start = ft_strchr(start, '"');
	start = ft_strchr(start + 1, '"');
	i = to_the_next_line(file, start - file);
	while (!(ft_isalpha(file[i])))
		i++;
	if (!(tab = ft_strsplit(file + i, '\n')))
		return (0);
	return (tab);
}

static	int		split_line(char *line, t_control *control)
{
	char		**tab;
	int			i;
	int			check;

	i = 0;
	check = 0;
	while (line[i])
	{
		if (line[i] != ' ' || line[i] != '\t')
			check++;
		i++;
	}
	if (check != 0)
		return (1);
	if ((tab = multi_split(line, SPLIT)) == NULL)
		return (-10);
	return (analyse_line(line, control, tab));
}

int				check_line_composition(char *file, t_control *control)
{
	char		**split;
	int			i;
	int			ret;

	if (has_instruction(file) < 0)
		return (-2);
	if (!(split = create_tab(file)))
		return (-1);
	i = 0;
	while (split[i])
	{
		if ((ret = split_line(split[i], control)) < 0)
			return (error_line_composition(split, ret, i));
		init_control(control);
		i++;
	}
	free_tab(split);
	return (1);
}
