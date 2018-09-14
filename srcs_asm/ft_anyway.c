/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_anyway.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lotoussa <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/27 21:12:40 by lotoussa     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/14 16:56:07 by lotoussa    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/asm.h"

char		*ft_strfjoin(char *s1, char *s2)
{
	size_t	len;
	char	*new;

	if (!s1)
	{
		if (!(new = ft_strdup(s2)))
			return (NULL);
		ft_strdel(&s2);
		return (new);
	}
	if (!s2)
	{
		if (!(new = ft_strdup(s1)))
			return (NULL);
		ft_strdel(&s1);
		return (new);
	}
	len = (ft_strlen(s1) + ft_strlen(s2));
	if (!(new = ft_memalloc(len + 1)))
		return (NULL);
	ft_strcat(new, s1);
	ft_strcat(new, s2);
	ft_strdel(&s1);
	ft_strdel(&s2);
	return (new);
}

int			ft_transform_comment(t_all *a, int i)
{
	char		*tmp;

	while (a->base.tkn[i])
	{
		if (!CMP(a->base.tkn[i], " #"))
			while (CMP(a->base.tkn[i], "\n"))
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
	while (a->base.tkn[i] && (!CMP(a->base.tkn[i], "#") || !CMP(a->\
					base.tkn[i], ".") || !CMP(a->base.tkn[i], "\n")))
	{
		while (a->base.tkn[i] && CMP(a->base.tkn[i], "\n"))
			i++;
		i++;
	}
	j = i;
	while (a->base.tkn[i])
	{
		if (!CMP(a->base.tkn[i], ";") || !CMP(a->base.tkn[i], "#"))
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
		while (CMP(((t_compl*)tmp->content)->tkn, "\n"))
		{
			ch[0] += (((t_compl*)tmp->content)->type == _PAR ? 1 : 0);
			ch[1] += (((t_compl*)tmp->content)->type == _LAB ? 1 : 0);
			ch[2] += (((t_compl*)tmp->content)->type == _SEP ? 1 : 0);
			ch[3] += (((t_compl*)tmp->content)->type == _INS ? 1 : 0);
			tmp = tmp->next;
		}
		if ((ch[2] && !ch[1] && ch[0] && !ch[3]) || (ch[1] && ch[0] && !ch[3]))
		{
			ft_putstr("Lexical error at line ");
			ft_putnbr(((t_compl*)tmp->content)->line);
			ft_putchar('\n');
			return (1);
		}
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
