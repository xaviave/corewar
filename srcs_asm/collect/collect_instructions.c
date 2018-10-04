/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   collect_instructions.c                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xmoreau <xmoreau@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/28 14:31:58 by xmoreau      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/04 15:56:41 by xmoreau     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/asm.h"

static char		**get_tab_of_instruction(t_infos *infos)
{
	char		**tab;
	char		*start;
	int			i;

	start = ft_strstr(infos->file, COMMENT_CMD_STRING);
	start = ft_strchr(start, '"');
	start = ft_strchr(start + 1, '"');
	i = to_the_next_line(infos->file, start - infos->file);
	while (!(ft_isalpha(infos->file[i])))
		i++;
	if (!(tab = ft_strsplit(infos->file + i, '\n')))
		return (NULL);
	return (tab);
}

static int		init_for_norm(int *ret, t_stock *stock)
{
	*ret = 0;
	if (stock->label == NULL)
		return (*ret);
	return (1);
}

static int		start_by_new_label(char *s, t_stock *stock)
{
	int			ret;
	t_label		*tmp;
	char		*to_compare;

	if (init_for_norm(&ret, stock) == 0)
		return (ret);
	tmp = *(stock->label);
	while (tmp)
	{
		if (ft_strstr(s, tmp->name) && ft_strchr(s, LABEL_CHAR))
		{
			if (!(to_compare = ft_strsub(s, 0, ft_strlen(s) - 1)))
				return (0);
			if (ft_strcmp(tmp->name, to_compare) == 0)
			{
				stock->lab = tmp;
				ret = 1;
				ft_strdel(&to_compare);
				break ;
			}
			ft_strdel(&to_compare);
		}
		tmp = tmp->next;
	}
	return (ret);
}

void			collect_instructions(t_label **label,
				t_cmd **cmd, t_infos *infos)
{
	int			i;
	char		**tab;
	char		**instru;
	t_stock		stock;
	int			j;

	if ((tab = get_tab_of_instruction(infos)) == NULL)
		error_instru(cmd, 1000, &stock, NULL);
	stock.lab = NULL;
	stock.label = label;
	stock.inf = infos;
	i = -1;
	while (tab[++i])
	{
		if (!(instru = multi_split(tab[i], SPLIT)))
			return ;
		j = start_by_new_label(instru[0], &stock);
		if ((j = new_cmd(cmd, instru, j, &stock)) < 0)
		{
			free_tab(tab);
			error_instru(cmd, -j, &stock, instru);
		}
		free_tab(instru);
	}
	free_tab(tab);
}
