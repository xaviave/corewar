/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   collect_header_and_label.c                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xmoreau <xmoreau@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/23 14:45:16 by tduverge     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/02 11:43:20 by lotoussa    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/asm.h"

static void		finish_with_newline(char *file)
{
	int			i;
	int			j;

	i = 0;
	j = -1;
	while (file[i])
	{
		i++;
		j++;
	}
	if (file[j] != '\n')
	{
		ft_printf("Syntax error - unexpected end of input ");
		ft_printf("Perhaps you forgot to end with a newline ?)\n");
		exit(1);
	}
}

void			collect_header_and_labels(t_label **label,
				header_t *header, t_infos infos)
{
	int		i;
	int		step;

	i = 0;
	step = 0;
	finish_with_newline(infos.file);
	while (infos.file[i])
	{
		i = to_the_next_char(infos.file, i);
		if (infos.file[i] && infos.file[i] != '\n'
		&& infos.file[i] != COMMENT_CHAR)
		{
			i = step == 0 ? collect_name(header, infos.file, i) : i;
			i = step == 1 ? collect_comment(header, infos.file, i) : i;
			i = step == 2 ? collect_label(label, infos.file, i) : i;
			step == 0 || step == 1 ? step++ : 0;
		}
		else
			i = to_the_next_line(infos.file, i);
	}
	header->magic = COREWAR_EXEC_MAGIC;
}
