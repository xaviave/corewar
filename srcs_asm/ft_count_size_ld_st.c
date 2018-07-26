#include "../includes/asm.h"

void		ft_count_size_ld_st(char *tkn, t_list **tmp, int *size)
{
	t_list		*inc;
	int			par;

	inc = *tmp;
	par = 0;
	if (!ft_strcmp(tkn, "ld"))
	{
		while (inc && ft_strcmp(((t_compl*)inc->content)->tkn, "\n"))
		{
			par = (((t_compl*)inc->content)->par_type == _DIR ? 1 : par);
			inc = inc->next;
		}
		*tmp = (inc->next ? inc->next : inc);
		*size += (par ? 7 : 5);
	}
	else if (!ft_strcmp(tkn, "st"))
	{
		while (inc && ft_strcmp(((t_compl*)inc->content)->tkn, "\n"))
		{
			par = (((t_compl*)inc->content)->par_type == _IND ? 1 : par);
			inc = inc->next;
		}
		*tmp = (inc->next ? inc->next : inc);
		*size += (par ? 5 : 4);
	}
}
