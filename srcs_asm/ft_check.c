/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_check.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lotoussa <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/22 17:18:49 by lotoussa     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/25 19:34:24 by lotoussa    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/asm.h"

int			ft_add_elem(t_list **list, char *tkn, int l)
{
	t_list		*new;
	t_compl		cpl;
	int			i;
	int			c;

	i = 0;
	c = 0;
	new = NULL;
	if (tkn[i] == '\t')
	{
		while (tkn[i])
			c = (tkn[i++] != '\t') ? 1 : c;
		if (c == 0)
			return (1);
	}
	if (!(cpl.tkn = ft_strdup(tkn)))
		return (0);
	cpl.line = (ft_strcmp(tkn, "\n") ? l : l - 1);
	cpl.type = 0;
	cpl.par_type = 0;
	cpl.lab = 0;
	cpl.size = 0;
	if (!(new = ft_lstnew(&cpl, sizeof(cpl))))
		return (0);
	ft_lstpush(list, new);
	return (1);
}

t_list		*ft_organise_list(char **tkn)
{
	t_list		*list;
	int			i;
	int			l;

	i = 0;
	l = 1;
	list = NULL;
	while (tkn[i] && (!ft_strcmp(tkn[i], "#") || !ft_strcmp(tkn[i], ".")
				|| !ft_strcmp(tkn[i], "\n")))
	{
		l += ((!ft_strcmp(tkn[i], "\n") && i > 0
					&& ft_strcmp(tkn[i - 1], "\n")) ? 1 : 0);
		i = ft_increment_tkn(tkn, i, &l);
	}
	while (tkn[i])
	{
		i = (!ft_strcmp(tkn[i], "#")) ? ft_increment_tkn(tkn, i, &l) : i;
		while ((!ft_strcmp(tkn[i], " ") || !ft_strcmp(tkn[i], "\t")))
			i++;
		l += ((!ft_strcmp(tkn[i], "\n")) ? 1 : 0);
		i = (!ft_strcmp(tkn[i], "#")) ? ft_increment_tkn_second(tkn, i, &l) : i;
		if (!(ft_add_elem(&list, tkn[i++], l)))
			return (NULL);
	}
	return (list);
}

int			ft_detail_ligne(t_list *list)
{
	if (!(ft_check_detail(&list)))
		return (0);
	return (1);
}

int			ft_first_verif(t_all *a, char **tkn)
{
	int		i;

	i = 0;
	if (!(a->t = ft_organise_list(tkn)))
	{
		ft_printf("Code missing\n");
		return (0);
	}
	while (a->base.tkn[i])
		ft_strdel(&a->base.tkn[i++]);
	free(a->base.tkn);
	a->base.tkn = NULL;
	if (!(ft_detail_ligne(a->t)))
		return (0);
	return (1);
}

int			ft_check(t_all *a)
{
	if (!(ft_first_verif(a, a->base.tkn)))
		return (0);
	if (!(a->file_size = ft_count_size(a->t)))
	{
		ft_printf("Code missing\n");
		return (0);
	}
	if (!(ft_reform(a)))
		return (0);
	return (1);
}
