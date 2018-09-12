/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_free.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lotoussa <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/21 17:18:19 by lotoussa     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/12 17:24:17 by xamartin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/asm.h"

int			ft_free_things(char *s1, char **s2)
{
	int		i;

	i = 0;
	if (s1)
		ft_strdel(&s1);
	if (s2)
	{
		while (s2[i])
			ft_strdel(&s2[i++]);
		free(s2);
		s2 = NULL;
	}
	return (0);
}

int			ft_free_base(t_base *base)
{
	if (base->name)
		ft_strdel(&base->name);
	if (base->comment)
		ft_strdel(&base->comment);
	return (0);
}

char		*ft_arg(int argc, char **argv)
{
	char	*arg;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(_ARG) - 2;
	arg = ft_strnew(len);
	while (i < len)
	{
		arg[i] = _ARG[i];
		i++;
	}
	return (arg);
}

int			ft_attribute_create(t_list *tmp, t_list **list)
{
	t_list		*t;
	char		*dup;

	t = *list;
	dup = ft_strfjoin(ft_strdup(((t_compl*)tmp->content)->tkn + 1),
			ft_strdup(":"));
	while (t && CMP(((t_compl*)t->content)->tkn, dup))
		t = t->next;
	ft_strdel(&dup);
	return (((t_compl*)t->content)->par_type);
}

int			ft_attribute_last_lab(t_list **list)
{
	t_list		*t;

	t = *list;
	while (t)
	{
		if (((t_compl*)t->content)->par_type == _IND &&
				((t_compl*)t->content)->tkn[0] == ':')
			((t_compl*)t->content)->lab = ft_attribute_create(t, list) -
				((t_compl*)t->content)->size;
		if (((t_compl*)t->content)->lab < 0)
			((t_compl*)t->content)->lab = 65536 + ((t_compl*)t->content)->lab;
		t = t->next;
	}
	return (1);
}
