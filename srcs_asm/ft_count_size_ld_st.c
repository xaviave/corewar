/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_count_size_ld_st.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lotoussa <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/27 21:12:55 by lotoussa     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/05 17:09:59 by lotoussa    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/asm.h"

void		ft_count_size_ld_st(char *tkn, t_list **tmp, int *size)
{
	t_list		*inc;
	int			par;

	inc = *tmp;
	par = 0;
	if (!ft_strcmp(tkn, "ld"))
	{
		while (inc && ft_strcmp(((t_compl*)inc->content)->tkn, "\n"))
		{
			par = (((t_compl*)inc->content)->par_type == _DIR ? 1 : par);
			inc = inc->next;
		}
		*tmp = (inc->next ? inc->next : inc);
		*size += (par ? 7 : 5);
		if (((t_compl*)((t_list*)*tmp)->content)->size)
			*tmp = (*tmp)->next;
		((t_compl*)((t_list*)*tmp)->content)->size = *size;
	}
	else if (!ft_strcmp(tkn, "st"))
	{
		while (inc && ft_strcmp(((t_compl*)inc->content)->tkn, "\n"))
		{
			par = (((t_compl*)inc->content)->par_type == _IND ? 1 : par);
			inc = inc->next;
		}
		*tmp = (inc->next ? inc->next : inc);
		*size += (par ? 5 : 4);
		if (((t_compl*)((t_list*)*tmp)->content)->size)
			*tmp = (*tmp)->next;
		((t_compl*)((t_list*)*tmp)->content)->size = *size;
	}
}

int			ft_create_size_tab(t_list **list)
{
	t_list		*tmp;

	tmp = *list;
	return (1);
}
