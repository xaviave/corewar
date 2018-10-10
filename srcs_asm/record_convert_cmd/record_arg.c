/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   record_arg.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xmoreau <xmoreau@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/06 14:55:13 by xmoreau      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/08 12:08:43 by xmoreau     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/asm.h"

static unsigned char	good_param(char *s, int nb, t_cmd *new)
{
	unsigned char		check;

	check = T_IND;
	if (s[0] == 'r')
		check = T_REG;
	if (s[0] == '%')
		check = T_DIR;
	check = check & g_op_tab[new->opcode - 1].arg[nb - 1];
	return (check);
}

static	int				synlex(char check, t_label **label, char *s)
{
	char				*ptr;
	t_label				*lab;

	if (check == T_REG)
	{
		ptr = ft_strchr(s, 'r');
		if (ft_atoi(ptr + 1) > REG_NUMBER || ft_atoi(ptr + 1) < 1)
			return (-1);
	}
	if ((ptr = ft_strchr(s, LABEL_CHAR)))
	{
		lab = *label;
		while (lab)
		{
			if ((ft_strcmp(ptr + 1, lab->name) == 0))
				return (1);
			lab = lab->next;
		}
		if (lab == NULL)
			return (-2);
	}
	return (1);
}

int						record_arg(char *s, int pnb, t_stock *stock,
						t_cmd **new)
{
	t_cmd				*tmp;
	unsigned char		check;
	int					ret;

	tmp = *new;
	if (!(check = good_param(s, pnb, *new)))
		return (-3210 - pnb);
	if (!(check_arg(s, check)))
		return (-3210 - pnb);
	if ((ret = synlex(check, stock->label, s)) < 0)
		return (-3220 + ret);
	if (!(tmp->param[pnb - 1] = ft_strdup(s)))
		return (-1000);
	return (1);
}
