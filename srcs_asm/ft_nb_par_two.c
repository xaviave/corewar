/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_nb_par_two.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lotoussa <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/25 16:36:53 by lotoussa     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/25 16:49:40 by lotoussa    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/asm.h"

int			ft_suite_tdu(t_list *tmp)
{
	int		par;

	par = 0;
	while (ft_strcmp(((t_compl*)tmp->content)->tkn, "\n"))
	{
		if (((t_compl*)tmp->content)->par_type == _REG)
			par++;
		tmp = tmp->next;
	}
	return (par == 1 ? 1 : 0);
}

int			ft_suite_utd(t_list *tmp)
{
	int		par;

	par = 0;
	while (ft_strcmp(((t_compl*)tmp->content)->tkn, "\n"))
	{
		if (((t_compl*)tmp->content)->par_type == _REG
				|| ((t_compl*)tmp->content)->par_type == _DIR)
			par++;
		tmp = tmp->next;
	}
	return (par == 1 ? 1 : 0);
}

int			ft_nb_par_ud(t_list *tmp)
{
	int		par;

	par = 0;
	while (ft_strcmp(((t_compl*)tmp->content)->tkn, "\n") && par != 1)
	{
		if (((t_compl*)tmp->content)->par_type == _REG)
			par++;
		tmp = tmp->next;
	}
	if (par != 1)
		return (0);
	par = 0;
	while (ft_strcmp(((t_compl*)tmp->content)->tkn, "\n") && par != 1)
	{
		if (((t_compl*)tmp->content)->par_type == _REG
				|| ((t_compl*)tmp->content)->par_type == _IND)
			par++;
		tmp = tmp->next;
	}
	return (par == 1 ? 1 : 0);
}

int			ft_nb_par_utd(t_list *tmp)
{
	int		par;

	par = 0;
	while (ft_strcmp(((t_compl*)tmp->content)->tkn, "\n") && par != 1)
	{
		if (((t_compl*)tmp->content)->par_type == _REG)
			par++;
		tmp = tmp->next;
	}
	if (par != 1)
		return (0);
	par = 0;
	while (ft_strcmp(((t_compl*)tmp->content)->tkn, "\n") && par != 1)
	{
		if (((t_compl*)tmp->content)->par_type == _REG
				|| ((t_compl*)tmp->content)->par_type == _DIR
				|| ((t_compl*)tmp->content)->par_type == _IND)
			par++;
		tmp = tmp->next;
	}
	if (par != 1)
		return (0);
	return (ft_suite_utd(tmp));
}

int			ft_nb_par_aff(t_list *tmp)
{
	int		par;

	par = 0;
	while (ft_strcmp(((t_compl*)tmp->content)->tkn, "\n"))
	{
		if (((t_compl*)tmp->content)->par_type == _REG)
			par++;
		tmp = tmp->next;
	}
	return (par == 1 ? 1 : 0);
}
