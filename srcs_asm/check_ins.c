/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check_ins.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lotoussa <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/25 15:11:04 by lotoussa     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/05 19:20:01 by lotoussa    ###    #+. /#+    ###.fr     */
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
	if (!CMP(((t_compl*)tmp->content)->tkn, "\n"))
		tmp = tmp->next;
	while (tmp && CMP(((t_compl*)tmp->content)->tkn, "\n"))
	{
		if (((t_compl*)tmp->content)->type == _INS)
			c++;
		tmp = tmp->next;
	}
	return (c == 1 ? 1 : 0);
}

int			ft_ins_type(char *tkn)
{
	if (!CMP(tkn, "live") || !CMP(tkn, "zjmp") || !CMP(tkn, \
				"fork") || !CMP(tkn, "lfork") || !CMP(tkn, "aff"))
		return (1);
	if (!CMP(tkn, "ld") || !CMP(tkn, "st") ||
			!CMP(tkn, "lld"))
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
	while (tmp && CMP(((t_compl*)tmp->content)->tkn, "\n"))
	{
		par += (((t_compl*)tmp->content)->type == _PAR ? 1 : 0);
		bug += (((t_compl*)tmp->content)->type == _SEP ? 1 : 0);
		sep += (!CMP(((t_compl*)tmp->content)->tkn, ",") ? 1 : 0);
		bug -= (!CMP(((t_compl*)tmp->content)->tkn, "\t")
			|| !CMP(((t_compl*)tmp->content)->tkn, ",")
			|| !CMP(((t_compl*)tmp->content)->tkn, " ") ? 1 : 0);
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
	if (!CMP(t, "live") || !CMP(t, "zjmp")
			|| !CMP(t, "fork") || !CMP(t, "lfork"))
		ret = (!ft_nb_par_u(tmp)) ? 0 : 1;
	else if (!CMP(t, "and") || !CMP(t, "or")
			|| !CMP(t, "xor"))
		ret = (!ft_nb_par_ttu(tmp)) ? 0 : 1;
	else if (!CMP(t, "add") || !CMP(t, "sub"))
		ret = (!ft_nb_par_uuu(tmp)) ? 0 : 1;
	else if (!CMP(t, "ldi") || !CMP(t, "lldi"))
		ret = (!ft_nb_par_tdu(tmp)) ? 0 : 1;
	else if (!CMP(t, "ld") || !CMP(t, "lld"))
		ret = (!ft_nb_par_du(tmp)) ? 0 : 1;
	else if (!CMP(t, "st"))
		ret = (!ft_nb_par_ud(tmp)) ? 0 : 1;
	else if (!CMP(t, "sti"))
		ret = (!ft_nb_par_utd(tmp)) ? 0 : 1;
	else if (!CMP(t, "aff"))
		ret = (!ft_nb_par_aff(tmp)) ? 0 : 1;
	return (ret ? 1 : 0);
}
