/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   calcul_size.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xmoreau <xmoreau@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/27 17:35:09 by xmoreau      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/04 15:56:49 by xmoreau     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/asm.h"

static char			analyse_bytecode(char param, unsigned char bc)
{
	if (param == 1)
		return (bc >> 6);
	if (param == 2)
		return ((bc >> 4) % 4);
	if (param == 3)
		return ((bc >> 2) % 4);
	return (0);
}

static char			choose_size(char tmp, char dsize)
{
	if (tmp == 1)
		return (1);
	if (tmp == 2)
		return (dsize);
	if (tmp == 3)
		return (IND_SIZE);
	return (0);
}

static void			multi_param(t_cmd **created, char dsize)
{
	t_cmd			*new;
	char			tmp;
	char			par;

	new = *created;
	new->size++;
	par = g_op_tab[new->opcode - 1].nb_arg;
	while (par)
	{
		tmp = analyse_bytecode(par, new->bytecode);
		new->size_param[par - 1] = choose_size(tmp, dsize);
		new->size += new->size_param[par - 1];
		if (!(new->byte_param[par - 1] =
		ft_memalloc(sizeof(char) * new->size_param[par - 1])))
			return ;
		par--;
	}
}

void				calcul_size(t_cmd **created)
{
	char			dsize;
	t_cmd			*new;

	new = *created;
	new->size = 1;
	dsize = DIR_SIZE;
	if (g_op_tab[new->opcode - 1].dir_size)
		dsize = DIR_SIZE / 2;
	if (new->bytecode == 0)
	{
		new->size += dsize;
		new->size_param[0] = dsize;
		if (!(new->byte_param[0] = ft_memalloc(sizeof(char) * dsize)))
			return ;
		return ;
	}
	else
		multi_param(created, dsize);
}
