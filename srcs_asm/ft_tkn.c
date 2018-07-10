#include "../includes/asm.h"

t_tkn		*ft_tknnew(char *nm)
{
	t_tkn	*new;

	if (!(new = (t_tkn *)malloc(sizeof(t_tkn))))
		return (NULL);
	if (!nm)
		new->nm = NULL;
	else
		new->nm = ft_strdup(nm);
	new->next = NULL;
	return (new);
}

void		ft_tknadd(t_tkn **tkn, t_tkn *new)
{
	new->next = *tkn;
	*tkn = new;
}

void		ft_tknpush(t_tkn **tkn, t_tkn *new)
{
	t_tkn	*cur;

	if (!(*tkn))
	{
		*tkn = new;
		return ;
	}
	cur = *tkn;
	while (cur->next)
		cur = cur->next;
	cur->next = new;
}
