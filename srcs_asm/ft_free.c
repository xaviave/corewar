/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_free.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lotoussa <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/21 17:18:19 by lotoussa     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/21 18:03:16 by lotoussa    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/asm.h"

int			ft_free_things(char *s1, char **s2)
{
	int		i;

	i = 0;
	if (s1)
		free(s1);
	if (s2)
	{
		while (s2[i])
			free(s2[i++]);
		free(s2);
	}
	return (0);
}

int			ft_free_base(t_base *base)
{
	if (base->name)
		free(base->name);
	if (base->comment)
		free(base->comment);
	return (0);
}
