/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   analyse_line.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xmoreau <xmoreau@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/02 13:30:30 by xmoreau      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/02 18:20:30 by xmoreau     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/asm.h"

static int		check_coma_position(char *line, char **tab, t_control *control)
{
	int			i;
	char		*com;
	char		*param;

	i = ft_strlen(line) - 1;
	while (line[i] == ' ' || line[i] == '\t')
		i--;
	if (line[i] == ',')
		return (-1);
	com = ft_strchr(line, ',');
	param = ft_strstr(line, tab[control->label + 1]);
	if (param > com)
		return (-1);
	if (control->nb_param == 2)
		return (1);
	i = 1;
	while (com[i] == ' ' || com[i] == '\t')
		i++;
	if (com[i] == ',')
		return (-1);
	return (1);
}

static int		check_coma(char *line, char **tab, t_control *control)
{
	int			i;

	i = 0;
	while (line[i] != 0)
	{
		if (line[i] == ',')
			control->coma++;
		i++;
	}
	if (control->coma != control->nb_param - 1)
		return (-5);
	if (control->nb_param == 1 && control->coma == 0)
		return (1);
	if (check_coma_position(line, tab, control) < 0)
		return (-6);
	return (1);
}

static int		check_param(char **tab, int index, char opcode)
{
	int			param;

	param = 1;
	while (tab[index + param] != NULL)
		param++;
	if (param - 1 != g_op_tab[opcode - 1].nb_arg)
		return (-3)	;
	return (param - 1);
}

static int		check_label(char *first)
{
	if (first[ft_strlen(first) - 1] == ':')
		return (1);
	return (0);
}

int				analyse_line(char *line, t_control *control, char **tab)
{
	control->label = check_label(tab[0]);
	if (control->label == 1 && tab[1] == NULL)
	{
		free_tab(tab);
		return (1);
	}
	if ((control->opcode = get_opcode(tab[control->label])) == 0)
	{
		free_tab(tab);
		return (-3);
	}
	if ((control->nb_param = check_param(tab, control->label,
	control->opcode)) < 0)
	{
		free_tab(tab);
		return (-4);
	}
	if ((control->coma = check_coma(line, tab, control)) < 0)
	{
		free_tab(tab);
		return (-5);
	}
	free_tab(tab);
	return (1);
}
