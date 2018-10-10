/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_size_and_adress.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xmoreau <xmoreau@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/06 16:35:41 by xmoreau      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/04 15:56:51 by xmoreau     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/asm.h"

static	int		calcul_adresse(t_cmd **cmd, t_cmd *new)
{
	t_cmd	*tmp;
	int		add;

	tmp = *cmd;
	add = 0;
	if (tmp == new)
		return (0);
	while (tmp && tmp->next != new)
		tmp = tmp->next;
	add = tmp->add + tmp->size;
	return (add);
}

static void		calcul_adresse_label(t_stock *stock, t_cmd *new)
{
	t_label		*tmp;

	if (stock->label == NULL)
		return ;
	tmp = *(stock->label);
	if (stock->lab->add == -1)
		stock->lab->add = new->add;
}

void			get_size_and_adress(t_cmd **cmd,
				t_cmd **created, t_stock *stock)
{
	t_cmd	*first;
	t_cmd	*new;

	new = *created;
	first = *cmd;
	calcul_size(created);
	new->add = calcul_adresse(cmd, new);
	if (stock->lab != NULL)
		calcul_adresse_label(stock, new);
}
