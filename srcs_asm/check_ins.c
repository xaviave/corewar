/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check_ins.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lotoussa <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/25 15:11:04 by lotoussa     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/25 16:41:27 by lotoussa    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/asm.h"

int			ft_check_nb_ins_line(t_list *tmp, t_list **list)
{
	int		c;
	t_list	*l;

	c = 0;
	l = *list;
	while (((t_compl*)l->content)->line != ((t_compl*)tmp->content)->line)
		l = l->next;
	tmp = l;
	if (!ft_strcmp(((t_compl*)tmp->content)->tkn, "\n"))
		tmp = tmp->next;
	while (tmp && ft_strcmp(((t_compl*)tmp->content)->tkn, "\n"))
	{
		if (((t_compl*)tmp->content)->type == _INS)
			c++;
		tmp = tmp->next;
	}
	return (c == 1 ? 1 : 0);
}

int			ft_ins_type(char *tkn)
{
	if (!ft_strcmp(tkn, "live") || !ft_strcmp(tkn, "zjmp") || !ft_strcmp(tkn, \
				"fork") || !ft_strcmp(tkn, "lfork") || !ft_strcmp(tkn, "aff"))
		return (1);
	if (!ft_strcmp(tkn, "ld") || !ft_strcmp(tkn, "st") ||
			!ft_strcmp(tkn, "lld"))
		return (2);
	return (3);
}

int			ft_check_nb_ins_par(t_list *tmp)
{
	int		c;
	int		par;
	int		sep;
	int		bug;

	c = ft_ins_type(((t_compl*)tmp->content)->tkn);
	par = 0;
	sep = 0;
	bug = 0;
	while (tmp && ft_strcmp(((t_compl*)tmp->content)->tkn, "\n"))
	{
		par += (((t_compl*)tmp->content)->type == _PAR ? 1 : 0);
		bug += (((t_compl*)tmp->content)->type == _SEP ? 1 : 0);
		sep += (!ft_strcmp(((t_compl*)tmp->content)->tkn, ",") ? 1 : 0);
		bug -= (!ft_strcmp(((t_compl*)tmp->content)->tkn, "\t")
			|| !ft_strcmp(((t_compl*)tmp->content)->tkn, ",")
			|| !ft_strcmp(((t_compl*)tmp->content)->tkn, " ") ? 1 : 0);
		tmp = tmp->next;
	}
	if ((c == 1 && par == 1 && sep == 0 && !bug)
		|| (c == 2 && par == 2 && sep == 1 && !bug)
		|| (c == 3 && par == 3 && sep == 2 && !bug))
		return (1);
	return (0);
}

int			ft_check_ins_type_par(t_list *tmp, char *t)
{
	int		ret;

	ret = 0;
	if (!ft_strcmp(t, "live") || !ft_strcmp(t, "zjmp")
			|| !ft_strcmp(t, "fork") || !ft_strcmp(t, "lfork"))
		ret = (!ft_nb_par_u(tmp)) ? 0 : 1;
	else if (!ft_strcmp(t, "and") || !ft_strcmp(t, "or")
			|| !ft_strcmp(t, "xor"))
		ret = (!ft_nb_par_ttu(tmp)) ? 0 : 1;
	else if (!ft_strcmp(t, "add") || !ft_strcmp(t, "sub"))
		ret = (!ft_nb_par_uuu(tmp)) ? 0 : 1;
	else if (!ft_strcmp(t, "ldi") || !ft_strcmp(t, "lldi"))
		ret = (!ft_nb_par_tdu(tmp)) ? 0 : 1;
	else if (!ft_strcmp(t, "ld") || !ft_strcmp(t, "lld"))
		ret = (!ft_nb_par_du(tmp)) ? 0 : 1;
	else if (!ft_strcmp(t, "st"))
		ret = (!ft_nb_par_ud(tmp)) ? 0 : 1;
	else if (!ft_strcmp(t, "sti"))
		ret = (!ft_nb_par_utd(tmp)) ? 0 : 1;
	else if (!ft_strcmp(t, "aff"))
		ret = (!ft_nb_par_aff(tmp)) ? 0 : 1;
	return (ret ? 1 : 0);
}
