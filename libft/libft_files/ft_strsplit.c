/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strsplit.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tduverge <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/26 11:28:47 by tduverge     #+#   ##    ##    #+#       */
/*   Updated: 2018/04/26 11:28:47 by tduverge    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../header/libft.h"

static int	count_words(char const *s, char c)
{
	int		x;
	int		ret;

	x = -1;
	ret = s[0] == c ? 0 : 1;
	while (s[++x])
		if (s[x] == c && s[x + 1] != c && s[x + 1] != '\0')
			ret++;
	return (ret);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**ret;
	int		nb_words;
	int		start;
	int		end;

	nb_words = count_words(s, c);
	if (!(ret = (char**)ft_memalloc(sizeof(char*) * (nb_words + 1))))
		return (NULL);
	end = ft_strlen(s) - 1;
	while (nb_words)
	{
		while (s[end] == c && end >= 0)
			end--;
		start = end;
		while (s[start] != c && start >= 0)
			start--;
		ret[nb_words - 1] = ft_strsub(s, start + 1, end - start);
		end = start;
		nb_words--;
	}
	return (ret);
}
