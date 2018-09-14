/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main_asm.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tduverge <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/25 12:04:14 by tduverge     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/14 17:34:32 by lotoussa    ###    #+. /#+    ###.fr     */
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
		((t_compl*)((t_list*)*alst)->content)->lab = 0;
		((t_compl*)((t_list*)*alst)->content)->size = 0;
		free(((t_compl*)((t_list*)*alst)->content));
		if ((*alst)->next)
			ft_lstdel_m(&((*alst)->next));
		free(*alst);
		*alst = (NULL);
	}
}

int		ft_free_all(t_all *a, int ret)
{
	int		i;

	i = 0;
	ft_strdel(&a->base.name);
	ft_strdel(&a->base.comment);
	if (a->base.tkn)
	{
		while (a->base.tkn[i])
			ft_strdel(&a->base.tkn[i++]);
		free(a->base.tkn);
		a->base.tkn = NULL;
	}
	ft_strdel(&a->file_name);
	a->file_size = 0;
	ft_lstdel_m(&a->t);
	if (ret)
		return (0);
	exit(1);
}

int		main(int argc, char **argv)
{
	char	*file;
	t_all	a;

	file = ft_first(argc, argv);
	a = ft_parsing(&file);
	if (!(ft_anyway(&a)))
		ft_free_all(&a, 0);
	if (!ft_check(&a))
		ft_free_all(&a, 0);
	if (!(ft_third(argv, argc, &a)))
		ft_free_all(&a, 0);
	ft_free_all(&a, 1);
	return (0);
}
