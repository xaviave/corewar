/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   bad_usage.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xmoreau <xmoreau@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/04 10:36:47 by xmoreau      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/04 14:40:13 by xmoreau     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/asm.h"

int				usage(void)
{
	ft_printf("Usage: ./exe_asm [-a] <sourcefile.s>\n");
	ft_printf("\t-a : Instead of creating a .cor file, outputs a stripped ");
	ft_printf("and annotated version of the code to the standard output\n");
	return (0);
}

int				empty_file(char *path)
{
	if (path != NULL)
		ft_printf("Your file %s is empty.\n", path);
	return (0);
}

int				has_instruction(char *file)
{
	char		*start;
	int			i;
	int			check;

	start = ft_strstr(file, COMMENT_CMD_STRING);
	start = ft_strchr(start, '"');
	start = ft_strchr(start + 1, '"');
	i = 1;
	check = 0;
	while (start[i] != '\0')
	{
		if (ft_isalnum(start[i]))
			check++;
		i++;
	}
	if (check == 0)
	{
		ft_printf("Your file appears to be without instructions.\n");
		return (-2);
	}
	return (1);
}
