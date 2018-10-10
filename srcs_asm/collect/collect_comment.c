/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   collect_comment.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xmoreau <xmoreau@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/27 13:45:32 by xmoreau      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/04 15:56:40 by xmoreau     ###    #+. /#+    ###.fr     */
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
		ft_printf("Champion comment too long (Max length 2048)\n");
	ft_strdel(&file);
	exit(1);
	return (0);
}

static int		record_comment(char *file, int i, t_header *header)
{
	int		j;

	j = 0;
	i++;
	while (j <= COMMENT_LENGTH + 1)
	{
		header->comment[j] = 0;
		j++;
	}
	j = 0;
	while (file[i] && file[i] != '"')
	{
		if (file[i] == '"')
			break ;
		if (j == COMMENT_LENGTH)
			return (error(file, i, 2));
		header->comment[j] = file[i];
		j++;
		i++;
	}
	return (i);
}

int				collect_comment(t_header *header, char *file, int i)
{
	if (!start_by(file + i, COMMENT_CMD_STRING))
		return (error(file, i, 1));
	i += ft_strlen(COMMENT_CMD_STRING);
	i = to_the_next_char(file, i);
	if (file[i] != '"')
		return (error(file, i, 1));
	i = record_comment(file, i, header);
	i = to_the_next_line(file, i);
	return (i);
}
