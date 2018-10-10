/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check_arg.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xmoreau <xmoreau@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/01 15:06:28 by lotoussa     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/05 14:14:31 by xmoreau     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/asm.h"

int			while_digit(char *s)
{
	int		i;

	i = 0;
	while (s[i])
		if (!ft_isdigit(s[i++]))
			return (0);
	return (1);
}

int			check_arg(char *arg, int type)
{
	if (type == T_REG)
	{
		if (!(while_digit(arg + 1)) || ft_strlen(arg) > 3)
			return (0);
	}
	else if (type == T_IND)
	{
		if (arg[0] == ':')
			return (1);
		if (arg[0] == '+' || !while_digit(arg[0] == '-' ? arg + 1 : arg))
			return (0);
	}
	else if (type == T_DIR)
	{
		if (!ft_strchr(arg, '-'))
			if (ft_strlen(arg) < 2 || (arg[1] != ':' && !while_digit(arg + 1)))
				return (0);
		if (ft_strchr(arg, '-'))
			if (ft_strlen(arg) < 3 || (arg[1] != ':' && !while_digit(arg + 2)))
				return (0);
	}
	return (1);
}
