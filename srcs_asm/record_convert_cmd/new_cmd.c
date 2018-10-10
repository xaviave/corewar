/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   new_cmd.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xmoreau <xmoreau@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/29 17:23:43 by xmoreau      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/05 12:01:19 by xmoreau     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/asm.h"

char			get_opcode(char *s)
{
	int			i;

	i = 0;
	while (i < 16)
	{
		if (ft_strequ(s, g_op_tab[i].name) == 1)
			return (g_op_tab[i].opcode);
		i++;
	}
	return (0);
}

int				get_args(char **tab, int j, t_cmd **new, t_stock *stock)
{
	int			pnb;
	t_cmd		*tmp;
	int			ret;

	pnb = 1;
	tmp = *new;
	while (tab[pnb + j])
		pnb++;
	pnb--;
	if (pnb != g_op_tab[(tmp->opcode - 1)].nb_arg)
	{
		return (-3100);
	}
	while (pnb)
	{
		if ((ret = record_arg(tab[j + pnb], pnb, stock, new)) < 0)
			return (ret);
		pnb--;
	}
	return (1);
}

static void		attach_to_list(t_cmd **cmd, t_cmd **new)
{
	t_cmd		*tmp;
	t_cmd		*tmpnew;

	tmp = *cmd;
	tmpnew = *new;
	if (tmp == NULL)
		*cmd = tmpnew;
	else
	{
		while (tmp->next != NULL && tmp)
			tmp = tmp->next;
		tmp->next = tmpnew;
	}
}

int				new_cmd(t_cmd **cmd, char **tab, int j, t_stock *stock)
{
	t_cmd		*new;
	int			ret;

	if (!(tab[j]))
		return (0);
	if (!(new = (t_cmd*)ft_memalloc(sizeof(t_cmd))))
		return (-1000);
	new->next = NULL;
	attach_to_list(cmd, &new);
	if (!(new->opcode = get_opcode(tab[j])))
		return (-2000);
	if ((ret = get_args(tab, j, &new, stock)) < 0)
		return (ret);
	if (g_op_tab[new->opcode - 1].codage)
		new->bytecode = get_bytecode(tab, j, new);
	get_size_and_adress(cmd, &new, stock);
	return (1);
}
