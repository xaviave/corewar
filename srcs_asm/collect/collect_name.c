/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   collect_name.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xmoreau <xmoreau@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/23 15:31:41 by tduverge     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/04 15:56:42 by xmoreau     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/asm.h"

static int		error(char *file, int i, int err_nb)
{
	int		coline[2];

	if (err_nb == 1)
	{
		give_coline(file, i, coline);
		ft_printf("Lexical error at [%d:%d]\n", coline[0], coline[1]);
	}
	if (err_nb == 2)
		ft_printf("Champion name too long (Max length 128)\n");
	ft_strdel(&file);
	exit(1);
	return (0);
}

static int		record_the_name(char *file, int i, t_header *header)
{
	int		j;

	j = 0;
	i++;
	while (j < PROG_NAME_LENGTH + 1)
	{
		header->prog_name[j] = 0;
		j++;
	}
	j = 0;
	while (file[i] && file[i] != '"')
	{
		if (file[i] == '"')
			break ;
		if (j == PROG_NAME_LENGTH)
			return (error(file, i, 2));
		header->prog_name[j] = file[i];
		j++;
		i++;
	}
	return (i);
}

int				collect_name(t_header *header, char *file, int i)
{
	if (!start_by(file + i, NAME_CMD_STRING))
		return (error(file, i, 1));
	i += ft_strlen(NAME_CMD_STRING);
	i = to_the_next_char(file, i);
	if (file[i] != '"')
		return (error(file, i, 1));
	i = record_the_name(file, i, header);
	i = to_the_next_line(file, i);
	return (i);
}
