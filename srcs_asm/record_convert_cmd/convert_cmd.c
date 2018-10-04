/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   convert_cmd.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xmoreau <xmoreau@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/05 13:41:53 by xmoreau      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/04 15:56:50 by xmoreau     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/asm.h"

static int			get_label_adress(char *str, t_label **label, int instru_add)
{
	t_label			*lab;

	lab = *label;
	while (*str != ':')
		str++;
	str++;
	while (lab)
	{
		if (ft_strcmp(str, lab->name) == 0)
			return (lab->add - instru_add);
		lab = lab->next;
	}
	return (0);
}

static void			transfer_bytes(t_cmd **cmd, int par, long nb)
{
	t_cmd			*line;
	int				len;

	line = *cmd;
	len = line->size_param[par];
	if (len == 1)
		line->byte_param[par][0] = nb & 0xff;
	if (len == 2)
	{
		line->byte_param[par][1] = nb & 0xff;
		line->byte_param[par][0] = (nb & 0xff00) >> 8;
	}
	if (len == 3)
	{
		line->byte_param[par][2] = nb & 0xff;
		line->byte_param[par][1] = (nb & 0xff00) >> 8;
		line->byte_param[par][0] = (nb & 0xff0000) >> 16;
	}
	if (len == 4)
	{
		line->byte_param[par][3] = nb & 0xff;
		line->byte_param[par][2] = (nb & 0xff00) >> 8;
		line->byte_param[par][1] = (nb & 0xff0000) >> 16;
		line->byte_param[par][0] = (nb & 0xff000000) >> 24;
	}
}

static void			from_str_to_byte(t_cmd **cmd, t_label **label, int par)
{
	long			nb;
	t_cmd			*line;

	nb = 0;
	line = *cmd;
	if (line->param[par][0] == 'r')
		nb = ft_long_atoi(line->param[par] + 1);
	else if (line->param[par][0] == '%' && line->param[par][1] == ':')
		nb = get_label_adress(line->param[par], label, line->add);
	else if (line->param[par][0] == '%' && line->param[par][1] != ':')
		nb = ft_long_atoi(line->param[par] + 1);
	else if (line->param[par][0] == ':')
		nb = get_label_adress(line->param[par], label, line->add);
	else
		nb = ft_atoi(line->param[par]);
	line->value_param[par] = nb;
	transfer_bytes(cmd, par, nb);
}

void				convert_param(t_cmd **cmd, t_label **label)
{
	t_cmd			*line;
	int				par;

	line = *cmd;
	while (line)
	{
		par = 3;
		while (par)
		{
			if (line->param[par - 1])
				from_str_to_byte(&line, label, par - 1);
			par--;
		}
		line = line->next;
	}
}
