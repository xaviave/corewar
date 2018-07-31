/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_print_size.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lotoussa <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/27 21:03:58 by lotoussa     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/27 21:50:31 by lotoussa    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/asm.h"

int			ft_print_size(int size, int fd)
{
	unsigned char		*tab;
	int					i;

	i = 0;
	ft_print_zero(fd, 4);
	if (!(tab = malloc(sizeof(unsigned char) * 4)))
		return (0);
	tab[0] = (size & 0xFF000000) >> 24;
	tab[1] = (size & 0xFF0000) >> 16;
	tab[2] = (size & 0xFF00) >> 8;
	tab[3] = (size & 0xFF);
	while (i < 4)
		fd_printf("%c", fd, tab[i++]);
	free(tab);
	tab = NULL;
	return (1);
}
