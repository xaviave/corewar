/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check_pre_parsing.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xmoreau <xmoreau@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/01 13:09:23 by xmoreau      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/04 13:26:58 by xmoreau     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/asm.h"

void			init_control(t_control *control)
{
	control->name = 0;
	control->comment = 0;
	control->label = 0;
	control->nb_param = 0;
	control->coma = 0;
	control->opcode = 0;
}

void			error_check(int err)
{
	if (err == -1)
		ft_printf("Your file lacks some element in the header\n");
	if (err == 1)
		ft_printf("Problem with memory allocation\n");
	if (err == 2)
		ft_printf("Syntax error for a COMMAND_NAME or COMMAND_COMMENT\n");
	exit(1);
}

static void		check_pre_parsing_follow(char **file, char **tab,
				t_control *control)
{
	int err;

	err = 0;
	if ((err = check_for_quote(*file)) == 0)
	{
		ft_strdel(file);
		free_tab(tab);
		error_check(2);
	}
	if ((err = check_line_composition(*file, control)) < 0)
	{
		ft_strdel(file);
		free_tab(tab);
		if (err == -1)
			error_check(1);
		exit(EXIT_FAILURE);
	}
	free_tab(tab);
}

void			check_pre_parsing(char **file)
{
	char		**tab;
	t_control	control;
	int			err;

	err = 0;
	init_control(&control);
	if ((tab = ft_strsplit(*file, '\n')) == NULL)
	{
		ft_strdel(file);
		error_check(1);
	}
	if ((err = check_name_comment(tab, &control)) < 0 ||
	(!control.name || !control.comment))
	{
		ft_strdel(file);
		free_tab(tab);
		error_check(err * -1);
	}
	check_pre_parsing_follow(file, tab, &control);
}
