#include "../includes/asm.h"

t_list		*ft_lexer(char *file)
{
	char	*tmp;
	t_list	*list;

	if (!(list = ft_lstnew(list, sizeof(t_list))))
		return (NULL);
}

int			ft_parsing(char *file)
{
	t_list		*list;

	if (!(list = ft_lexer(file)))
	{
		free(file);
		exit(1);
	}
}
