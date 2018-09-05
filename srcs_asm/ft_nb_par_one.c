/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_nb_par_one.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lotoussa <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/25 16:50:34 by lotoussa     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/05 19:20:32 by lotoussa    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/asm.h"

int			ft_nb_par_u(t_list *tmp)
{
	int		par;

	par = 0;
	while (CMP(((t_compl*)tmp->content)->tkn, "\n"))
	{
		if (((t_compl*)tmp->content)->par_type == _DIR)
			par++;
		tmp = tmp->next;
	}
	return (par == 1 ? 1 : 0);
}

int			ft_nb_par_ttu(t_list *tmp)
{
	int		par;

	par = 0;
	while (CMP(((t_compl*)tmp->content)->tkn, "\n") && par != 2)
	{
		if (((t_compl*)tmp->content)->par_type == _DIR ||
				((t_compl*)tmp->content)->par_type == _IND
				|| ((t_compl*)tmp->content)->par_type == _REG)
			par++;
		tmp = tmp->next;
	}
	if (par != 2)
		return (0);
	par = 0;
	while (CMP(((t_compl*)tmp->content)->tkn, "\n"))
	{
		if (((t_compl*)tmp->content)->par_type == _REG)
			par++;
		tmp = tmp->next;
	}
	return (par == 1 ? 1 : 0);
}

int			ft_nb_par_uuu(t_list *tmp)
{
	int		par;

	par = 0;
	while (CMP(((t_compl*)tmp->content)->tkn, "\n"))
	{
		if (((t_compl*)tmp->content)->par_type == _REG)
			par++;
		tmp = tmp->next;
	}
	return (par == 3 ? 1 : 0);
}

int			ft_nb_par_tdu(t_list *tmp)
{
	int		par;

	par = 0;
	while (CMP(((t_compl*)tmp->content)->tkn, "\n") && par != 1)
	{
		if (((t_compl*)tmp->content)->par_type == _DIR
				|| ((t_compl*)tmp->content)->par_type == _IND
				|| ((t_compl*)tmp->content)->par_type == _REG)
			par++;
		tmp = tmp->next;
	}
	if (par != 1)
		return (0);
	par = 0;
	while (CMP(((t_compl*)tmp->content)->tkn, "\n") && par != 1)
	{
		if (((t_compl*)tmp->content)->par_type == _DIR
				|| ((t_compl*)tmp->content)->par_type == _REG)
			par++;
		tmp = tmp->next;
	}
	if (par != 1)
		return (0);
	return (ft_suite_tdu(tmp));
}

int			ft_nb_par_du(t_list *tmp)
{
	int		par;

	par = 0;
	while (CMP(((t_compl*)tmp->content)->tkn, "\n") && par != 1)
	{
		if (((t_compl*)tmp->content)->par_type == _DIR
				|| ((t_compl*)tmp->content)->par_type == _IND)
			par++;
		tmp = tmp->next;
	}
	if (par != 1)
		return (0);
	par = 0;
	while (CMP(((t_compl*)tmp->content)->tkn, "\n"))
	{
		if (((t_compl*)tmp->content)->par_type == _REG)
			par++;
		tmp = tmp->next;
	}
	return (par == 1 ? 1 : 0);
}
