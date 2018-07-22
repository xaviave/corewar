/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_check.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lotoussa <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/22 17:18:49 by lotoussa     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/22 20:49:01 by lotoussa    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/asm.h"

int			ft_add_elem(t_list **list, char *tkn)
{
	t_list		*new;
	int			i;
	int			c;

	i = 0;
	c = 0;
	new = NULL;
	if (tkn[i] == '\t')
	{
		while (tkn[i])
			if (tkn[i++] != '\t')
				c = 1;
		if (c == 0)
			return (1);
	}
	if (!(new = ft_lstnew(tkn, sizeof(tkn))))
		return (0);
	ft_lstpush(list, new);
	return (1);
}

t_list		*ft_organise_list(char **tkn)
{
	t_list		*list;
	int			i;

	i = 0;
	list = NULL;
	while (tkn[i] && (!ft_strcmp(tkn[i], "#") || !ft_strcmp(tkn[i], ".")))
	{
		while (tkn[i] && ft_strcmp(tkn[i], "\n"))
			i++;
		i++;
	}
	while (tkn[i])
	{
		if (!ft_strcmp(tkn[i], "#"))
		{
			while (tkn[i] && ft_strcmp(tkn[i], "\n"))
				i++;
			i++;
		}
		if (!ft_strcmp(tkn[i], " ") || !ft_strcmp(tkn[i], "\t"))
			i++;
		ft_add_elem(&list, tkn[i++]);
	}
	return (list);
}

int			ft_first_verif(t_all *a, char **tkn)
{
	int		i;

	i = 0;
	if (!(a->t = ft_organise_list(tkn)))
		return (0);
	while (a->base.tkn[i])
		ft_strdel(&a->base.tkn[i]);
	free(a->base.tkn);
	a->base.tkn = NULL;
	return (1);
}

int			ft_check(t_all *a)
{
	if (!(ft_first_verif(a, a->base.tkn)))
		return (0);
	return (1);
}
