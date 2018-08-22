/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check_cor.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tduverge <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/22 14:24:12 by tduverge     #+#   ##    ##    #+#       */
/*   Updated: 2018/08/22 14:24:13 by tduverge    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/corewar.h"

int		check_cor_file(char *str)
{
	int		len;

	len = ft_strlen(str);
	if (len >= 4 && str[len - 1] == 'r' && str[len - 2] == 'o'
			&& str[len - 3] == 'c' && str[len - 4] == '.')
		return (1);
	return (0);
}

int		check_cor_nb(int ac, char **av)
{
	int	i;
	int	cor;

	cor = 0;
	i = 0;
	while (++i < ac)
	{
		if (check_cor_file(av[i]))
			cor++;
	}
	return (cor);
}
