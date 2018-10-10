/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   recalcul_label.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xmoreau <xmoreau@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/28 18:10:04 by xmoreau      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/04 15:56:52 by xmoreau     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/asm.h"

static void	re_calcul_adress(t_label **label)
{
	t_label	*first;
	t_label	*second;

	first = *label;
	while (first != NULL)
	{
		if (first->add == -1 && first->next != NULL)
		{
			second = first->next;
			while (second->next != NULL && second->add == -1)
				second = second->next;
			if (second != NULL)
				first->add = second->add;
		}
		first = first->next;
	}
}

static void	re_calcul_with_size(t_label **label, t_cmd *cmd)
{
	t_label	*first;
	t_label	*second;
	int		to_add;

	to_add = 0;
	first = *label;
	second = first->next;
	while (second && first)
	{
		if (second->add == -1)
		{
			while (cmd && cmd->add != first->add)
				cmd = cmd->next;
			while (cmd)
			{
				to_add += cmd->size;
				cmd = cmd->next;
			}
			second->add = first->add + to_add;
			return ;
		}
		first = second;
		second = second->next;
	}
}

static int	need_calcul(t_label *label)
{
	while (label)
	{
		if (label->add == -1)
			return (0);
		label = label->next;
	}
	return (1);
}

void		re_calculate_label_add(t_label **label, t_cmd *cmd)
{
	if (label == NULL)
		return ;
	if (need_calcul(*label))
		return ;
	re_calcul_adress(label);
	if (need_calcul(*label))
		return ;
	re_calcul_with_size(label, cmd);
}
