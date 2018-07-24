/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main_asm.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tduverge <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/25 12:04:14 by tduverge     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/22 17:18:35 by lotoussa    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/asm.h"

void	ft_lstdel_m(t_list **alst)
{
	if (*alst)
	{
		ft_strdel(&((t_compl*)((t_list*)*alst)->content)->tkn);
		((t_compl*)((t_list*)*alst)->content)->type = 0;
		((t_compl*)((t_list*)*alst)->content)->par_type = 0;
		((t_compl*)((t_list*)*alst)->content)->line = 0;
		free(((t_compl*)((t_list*)*alst)->content));
		if ((*alst)->next)
			ft_lstdel_m(&((*alst)->next));
		free(*alst);
		*alst = (NULL);
	}
}

int		ft_free_all(t_all *a)
{
	int		i;

	i = 0;
	ft_strdel(&a->base.name);
	ft_strdel(&a->base.comment);
	if (a->base.tkn)
	{
		while (a->base.tkn[i])
			ft_strdel(&a->base.tkn[i++]);
		ft_strdel(a->base.tkn);
	}
	ft_strdel(&a->file_name);
	if (a->t)
		ft_lstdel_m(&a->t);
	return (0);
}

int		main(int argc, char **argv)
{
	char	*file;
	t_all	a;

	file = ft_first(argc, argv);
	a = ft_parsing(&file);
	if (!ft_check(&a))
		return (ft_free_all(&a));
	ft_third(argv, argc, &a);
	return (0);
}
