/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   to_the_next.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xmoreau <xmoreau@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/23 17:30:34 by tduverge     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/02 12:43:32 by lotoussa    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/asm.h"

int				to_the_next_char(char *str, int i)
{
	while (((str[i] >= 9) && (str[i] <= 13)) || (str[i] == ' '))
		i++;
	return (i);
}

int				to_the_next_line(char *str, int i)
{
	while (str[i] && str[i] != '\n')
		i++;
	return (str[i] == '\n' ? i + 1 : i);
}

char			*get_next_word(char *file, int i, char separator)
{
	int			j;
	char		error;
	char		*word;

	j = 0;
	if (separator == LABEL_CHAR)
		error = SEPARATOR_CHAR;
	else
		error = LABEL_CHAR;
	while (file[i + j] && file[i + j] != separator)
	{
		if (file[i + j] == error || ft_strchr(STOP_SIGN, file[i + j]) != NULL)
			return (NULL);
		j++;
	}
	if (!(word = ft_strsub(file, i, j)))
		return (NULL);
	return (word);
}
