/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_anyway.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lotoussa <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/27 21:12:40 by lotoussa     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/27 21:49:05 by lotoussa    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/asm.h"

int			ft_transform_comment(t_all *a, int i)
{
	char		*tmp;

	while (a->base.tkn[i])
	{
		if (!ft_strcmp(a->base.tkn[i], " #"))
			while (ft_strcmp(a->base.tkn[i], "\n"))
			{
				tmp = a->base.tkn[i];
				if (!(a->base.tkn[i] = ft_strdup(" ")))
					return (0);
				ft_strdel(&tmp);
				i++;
			}
		i++;
	}
	return (1);
}

int			ft_anyway(t_all *a)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (a->base.tkn[i] && (!ft_strcmp(a->base.tkn[i], "#") || !ft_strcmp(a->\
					base.tkn[i], ".") || !ft_strcmp(a->base.tkn[i], "\n")))
	{
		while (a->base.tkn[i] && ft_strcmp(a->base.tkn[i], "\n"))
			i++;
		i++;
	}
	j = i;
	while (a->base.tkn[i])
	{
		if (!ft_strcmp(a->base.tkn[i], ";") || !ft_strcmp(a->base.tkn[i], "#"))
		{
			tmp = a->base.tkn[i];
			if (!(a->base.tkn[i] = ft_strdup(" #")))
				return (0);
			ft_strdel(&tmp);
		}
		i++;
	}
	return (ft_transform_comment(a, j));
}

int			ft_only_sep(t_list **list)
{
	t_list		*tmp;
	int			ch[4];

	tmp = *list;
	while (tmp)
	{
		ft_bzero(&ch, sizeof(ch));
		while (ft_strcmp(((t_compl*)tmp->content)->tkn, "\n"))
		{
			ch[0] += (((t_compl*)tmp->content)->type == _PAR ? 1 : 0);
			ch[1] += (((t_compl*)tmp->content)->type == _LAB ? 1 : 0);
			ch[2] += (((t_compl*)tmp->content)->type == _SEP ? 1 : 0);
			ch[3] += (((t_compl*)tmp->content)->type == _INS ? 1 : 0);
			tmp = tmp->next;
		}
		if ((ch[2] && !ch[1] && ch[0] && !ch[3]) || (ch[1] && ch[0] && !ch[3]))
			return (ft_printf("Lexical error at line %d\n",
						((t_compl*)tmp->content)->line));
		tmp = tmp->next;
	}
	return (0);
}

int			ft_bad_line(t_list **list)
{
	if (ft_only_sep(list))
		return (0);
	return (1);
}
