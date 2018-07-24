/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_extend_check.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lotoussa <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/23 18:03:36 by lotoussa     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/23 20:31:54 by lotoussa    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/asm.h"

int			ft_dir_label(char *tkn, t_list **list)
{
	t_list		*tmp;
	char		*dup;
	char		*fre;
	int			c;

	tmp = *list;
	dup = ft_strdup(tkn + 2);
	fre = dup;
	dup = ft_strjoin(dup, ":");
	free(fre);
	c = 0;
	while (tmp && c == 0)
	{
		if (((t_compl*)tmp->content)->type == _LAB)
		{
			if (!ft_strcmp(dup, ((t_compl*)tmp->content)->tkn))
				c = 1;
		}
		tmp = tmp->next;
	}
	free(dup);
	return (c ? 1 : 0);
}

int			ft_check_par_alone(char *t, t_list *tmp, t_list **list)
{
	if (((t_compl*)tmp->content)->par_type == _DIR)
		if (ft_strlen(t) < 2 || (t[1] == ':' && !(ft_dir_label(t, list)))
				|| (t[1] != ':' && !ft_while_digit(t + 1)))
			return (0);
	if (((t_compl*)tmp->content)->par_type == _IND)
	{
		/* faire les indirect */
	}
	if (((t_compl*)tmp->content)->par_type == _REG)
		if (!(ft_while_digit(t + 1)) || ft_strlen(t) > 3)
			return (0);
	return (1);
}

int			ft_check_label_char(char *tkn, t_list *tmp)
{
	char	*check;
	int		i;
	int		j;
	int		c;

	i = 0;
	c = 0;
	check = ft_strdup(LABEL_CHARS);
	while (tkn[i] && tkn[i] != ':')
	{
		c = 0;
		j = 0;
		while (check[j] && c == 0)
			c = ((tkn[i] == check[j++]) ? 1 : 0);
		if (c == 0)
			break ;
		i++;
	}
	free(check);
	if (c == 0)
		ft_printf("Error at LABEL \"%s\" line %d\n",
				tkn, ((t_compl*)tmp->content)->line);
	return (c == 1 ? 1 : 0);
}
