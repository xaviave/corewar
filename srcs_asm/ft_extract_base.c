/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_extract_base.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lotoussa <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/21 17:18:49 by lotoussa     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/21 18:02:51 by lotoussa    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/asm.h"

char		*ft_extract_comment(char *line)
{
	char	*new;
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	while (line[i] && line[i] != '\"')
		i++;
	i++;
	if (!(new = ft_strdup(ft_strchr(line, '\"'))))
		return (0);
	tmp = ft_memalloc(ft_strlen(new) - 2);
	i = 1;
	j = 0;
	while (new[i] && new[i] != '\"')
		tmp[j++] = new[i++];
	free(new);
	return (tmp);
}
