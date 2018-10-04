/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   collect_label.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xmoreau <xmoreau@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/27 13:52:12 by xmoreau      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/04 15:56:42 by xmoreau     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/asm.h"

static int		error(char *file, int i, t_label **label)
{
	int			coline[2];

	give_coline(file, i, coline);
	ft_printf("Lexical error at [%d:%d]\n", coline[0], coline[1]);
	ft_strdel(&file);
	free_label(*label);
	exit(1);
	return (0);
}

static	void	new_label(t_label **label, char *name)
{
	t_label		*new;
	t_label		*tmp;

	if ((new = ft_memalloc(sizeof(t_label))) == NULL)
	{
		free_label(*label);
		ft_printf("Error with memory allocation\n");
		exit(1);
		return ;
	}
	new->name = name;
	new->add = -1;
	if (*label == NULL)
	{
		*label = new;
		return ;
	}
	tmp = *label;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
}

int				collect_label(t_label **label, char *file, int i)
{
	char		*word;
	int			j;

	if ((word = get_next_word(file, i, LABEL_CHAR)) == NULL)
		return (to_the_next_line(file, i));
	j = 0;
	while (word[j] != '\0')
	{
		if (ft_strchr(LABEL_CHARS, word[j]) == NULL)
			error(file, i, label);
		j++;
	}
	new_label(label, word);
	i = to_the_next_line(file, i);
	return (i);
}
