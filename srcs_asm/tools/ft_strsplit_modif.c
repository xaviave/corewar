/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strsplit_modif.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lotoussa <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/01 16:47:48 by lotoussa     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/02 12:53:40 by lotoussa    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/asm.h"

static int	count_words(char const *s, char c)
{
	int		x;
	int		ret;

	x = 0;
	ret = 0;
	while (s[x])
		ret += (s[x++] == c ? 1 : 0);
	return (ret);
}

static void	init_for_norm(int *i, int *nb_words)
{
	*i = -1;
	*nb_words = 0;
}

char		**ft_strsplit_modif(char const *s, char c)
{
	char		**ret;
	int			nb_words;
	int			i;
	int			start;

	nb_words = count_words(s, c);
	if (!(ret = (char**)ft_memalloc(sizeof(char*) * (nb_words + 1))))
		return (NULL);
	ret[nb_words] = NULL;
	init_for_norm(&i, &nb_words);
	while (s[++i])
		if (s[i] == '\n')
		{
			if (!(ret[nb_words++] = ft_strdup("\n")))
				return (NULL);
		}
		else
		{
			start = i;
			while (s[i] != '\n')
				i++;
			if (!(ret[nb_words++] = ft_strsub(s, start, i - start)))
				return (NULL);
		}
	return (ret);
}
