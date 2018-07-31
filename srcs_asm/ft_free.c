/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_free.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lotoussa <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/21 17:18:19 by lotoussa     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/22 20:24:23 by lotoussa    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/asm.h"

int			ft_free_things(char *s1, char **s2)
{
	int		i;

	i = 0;
	if (s1)
		ft_strdel(&s1);
	if (s2)
	{
		while (s2[i])
			ft_strdel(&s2[i++]);
		free(s2);
		s2 = NULL;
	}
	return (0);
}

int			ft_free_base(t_base *base)
{
	if (base->name)
		ft_strdel(&base->name);
	if (base->comment)
		ft_strdel(&base->comment);
	return (0);
}

char		*ft_arg(int argc, char **argv)
{
	char	*arg;
	char	*new;
	int		i;

	i = 0;
	arg = _ARG;
	new = ft_memalloc(ft_strlen(arg) - 1);
	while (i < (int)ft_strlen(arg) - 2)
	{
		new[i] = arg[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}
