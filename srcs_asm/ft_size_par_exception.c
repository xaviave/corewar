/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_size_par_exception.c                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lotoussa <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/05 13:43:57 by lotoussa     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/10 21:46:11 by lotoussa    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/asm.h"

void		ft_dir_lab_size_par(int fd, int oct, t_list *tmp)
{
	int		d;

	d = ((t_compl*)tmp->content)->lab - ((t_compl*)tmp->content)->size;
	ft_memrev((char*)&d, oct);
	write(fd, &d, oct);
}

void		ft_size_par_exception(int fd, int oct, t_list *tmp)
{
	int		d;

	if (((t_compl*)tmp->content)->tkn[1] == ':')
		ft_dir_lab_size_par(fd, oct, tmp);
	else
	{
		((t_compl*)tmp->content)->lab =
			ft_atoi(((t_compl*)tmp->content)->tkn + 1);
		d = ((t_compl*)tmp->content)->lab;
		ft_memrev((char*)&d, oct);
		write(fd, &d, oct);
	}
}

void		ft_memrev(char *ptr, size_t n)
{
	char		tmp;

	tmp = *ptr;
	*ptr = ptr[n - 1];
	ptr[n - 1] = tmp;
	if (n > 3)
		ft_memrev(ptr + 1, n - 2);
}
