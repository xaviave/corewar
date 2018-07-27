/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_anyway.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lotoussa <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/27 21:12:40 by lotoussa     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/27 21:49:05 by lotoussa    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/asm.h"

int			ft_anyway(t_all *a)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (a->base.tkn[i] && (!ft_strcmp(a->base.tkn[i], "#") || !ft_strcmp(a->\
					base.tkn[i], ".") || !ft_strcmp(a->base.tkn[i], "\n")))
	{
		while (a->base.tkn[i] && ft_strcmp(a->base.tkn[i], "\n"))
			i++;
		i++;
	}
	j = i;
	while (a->base.tkn[i])
	{
		if (!ft_strcmp(a->base.tkn[i], ";") || !ft_strcmp(a->base.tkn[i], "#"))
		{
			tmp = a->base.tkn[i];
			if (!(a->base.tkn[i] = ft_strdup(" #")))
				return (0);
			ft_strdel(&tmp);
		}
		i++;
	}
	return (1);
}
