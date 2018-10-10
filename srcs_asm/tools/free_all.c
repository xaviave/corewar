/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   free_all.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xmoreau <xmoreau@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/28 12:19:07 by xmoreau      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/04 15:56:53 by xmoreau     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/asm.h"

t_label		*free_label(t_label *label)
{
	t_label	*tmp;

	if (label == NULL)
		return (NULL);
	tmp = label->next;
	ft_memdel((void**)&label->name);
	ft_memdel((void**)&label);
	return (free_label(tmp));
}

t_cmd		*free_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		par;

	par = 3;
	if (cmd == NULL)
		return (NULL);
	tmp = cmd->next;
	while (par)
	{
		if (cmd->param[par - 1] != NULL)
			ft_memdel((void**)&cmd->byte_param[par - 1]);
		par--;
	}
	par = 3;
	while (par)
	{
		if (cmd->param[par - 1] != NULL)
			ft_memdel((void**)&cmd->param[par - 1]);
		par--;
	}
	ft_memdel((void**)&cmd);
	return (free_cmd(tmp));
}

void		free_infos(t_infos *infos)
{
	if (infos->file != NULL)
		ft_strdel(&infos->file);
}

int			free_all(t_label *label, t_infos *infos, t_cmd **cmd)
{
	if (infos != NULL)
		free_infos(infos);
	if (label != NULL)
		free_label(label);
	if (*cmd != NULL)
		free_cmd(*cmd);
	return (0);
}

void		free_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i] != NULL)
	{
		ft_strdel(&tab[i]);
		i++;
	}
	free(tab);
	tab = NULL;
}
