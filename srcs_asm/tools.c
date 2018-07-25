/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tools.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lotoussa <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/23 15:05:35 by lotoussa     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/25 19:16:21 by lotoussa    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/asm.h"

int			ft_while_digit(char *s)
{
	int		i;

	i = 0;
	while (s[i])
		if (!ft_isdigit(s[i++]))
			return (0);
	return (1);
}

int			ft_increment_tkn(char **tkn, int i, int *l)
{
	while (tkn[i] && ft_strcmp(tkn[i], "\n"))
		i++;
	if (!ft_strcmp(tkn[i], "\n"))
		(*l)++;
	i++;
	return (i);
}

int			ft_increment_tkn_second(char **tkn, int i, int *l)
{
	while (tkn[i] && ft_strcmp(tkn[i], "\n"))
		i++;
	if (!ft_strcmp(tkn[i], "\n"))
		(*l)++;
	return (i);
}
