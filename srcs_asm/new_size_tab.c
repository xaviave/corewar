/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   new_size_tab.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lotoussa <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/05 19:10:07 by lotoussa     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/05 19:32:33 by lotoussa    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/asm.h"

int			ft_ins_one(t_list *tmp)
{
	int		size;

	size = 2;
	while ((tmp = tmp->next) && ((t_compl*)tmp->content)->type == _PAR)
	{
		if (((t_compl*)tmp->content)->par_type == _REG)
			size++;
		if (((t_compl*)tmp->content)->par_type == _DIR)
			size += 4;
		if (((t_compl*)tmp->content)->par_type == _DIR)
			size += 2;
	}
	return (size);
}

int			ft_ins_two(t_list *tmp)
{
	int		size;

	size = 3;
	return (size);
}

int			ft_ins_three(t_list *tmp)
{
	int		size;

	size = 2;
	while ((tmp = tmp->next) && ((t_compl*)tmp->content)->type == _PAR)
	{
		if (((t_compl*)tmp->content)->par_type == _REG)
			size++;
		else if (((t_compl*)tmp->content)->par_type == _DIR
			|| ((t_compl*)tmp->content)->par_type == _IND)
			size += 2;
	}
	return (size);
}

int			ft_ins_four(t_list *tmp)
{
	int		size;

	size = 5;
	return (size);
}

int			ft_ins_five(t_list *tmp)
{
	int		size;
	int		par;

	size = 0;
	par = 0;
	if (!CMP(((t_compl*)tmp->content)->tkn, "ld"))
	{
		while ((tmp = tmp->next) && CMP(((t_compl*)tmp->content)->tkn, "\n"))
			par = (((t_compl*)tmp->content)->par_type == _DIR ? 1 : par);
		size += (par ? 7 : 5);
	}
	else
	{
		while ((tmp = tmp->next) && CMP(((t_compl*)tmp->content)->tkn, "\n"))
			par = (((t_compl*)tmp->content)->par_type == _IND ? 1 : par);
		size += (par ? 5 : 4);
	}
	return (size);
}
