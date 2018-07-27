/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_print_size.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lotoussa <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/27 21:03:58 by lotoussa     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/27 21:29:28 by lotoussa    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/asm.h"

int			ft_print_size(int size, int fd)
{
	unsigned char		*tab;

	tab = malloc(sizeof(unsigned char) * 4);
	tab[0] = (size & 0xFF000000) >> 24;
	tab[1] = (size & 0xFF0000) >> 16;
	tab[2] = (size & 0xFF00) >> 8;
	tab[3] = (size & 0xFF);
	fd_printf("%s", fd, tab);
	free(tab);
	return (1);
}
