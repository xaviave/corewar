/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_count_size_ld_st.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lotoussa <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/27 21:12:55 by lotoussa     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/05 18:28:30 by lotoussa    ###    #+. /#+    ###.fr     */
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

static int	ft_calcul_size_line(t_list *tmp)
{
	int		size;

	size = 0;
	return (size);
}

int			*ft_create_tab_size(t_list **list)
{
	t_list	*tmp;
	int		*tab;
	int		size;
	int		i;

	tmp = *list;
	size = ((t_compl*)tmp->content)->type == _LAB ? 0 : 1;
	while ((tmp = tmp->next))
		size += (((t_compl*)tmp->content)->type == _INS ? 1 : 0);
	if (!(tab = (int*)malloc(sizeof(int) * size)))
		return (0);
	tmp = *list;
	i = 0;
	tab[i++] = 0;
	while (tmp)
	{
		tmp = (((t_compl*)tmp->content)->type == _LAB ? tmp->next : tmp);
		tab[i++] = ft_calcul_size_line(tmp);
		while (((t_compl*)tmp->content)->type != _INS)
			tmp = tmp->next;
	}
	return (tab);
}

int			ft_create_size_tab(t_list **list)
{
	t_list		*tmp;
	int			*tab;
	int			line;
	int			i;

	tmp = *list;
	tab = ft_create_tab_size(list);
	i = 0;
	while (tmp)
	{
		line = ((t_compl*)tmp->content)->line;
		while (line == ((t_compl*)tmp->content)->line)
		{
			((t_compl*)tmp->content)->size = tab[i];
			tmp = tmp->next;
		}
		i++;
	}
	free(tab);
	tab = NULL;
	return (1);
}
