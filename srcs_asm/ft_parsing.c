#include "../includes/asm.h"

int			ft_char(char let)
{
	if (let == '.' || let == ' ' || let == '"' || let == '\n' || let == ',')
		return (0);
	else
		return (1);
}

t_list		*ft_lexer(char *file)
{
	char	*tkn;
	char	glu[2];
	char	*fre;
	t_list	*list;
	t_list	*tmp;

	if (!(list = ft_lstnew(list, sizeof(t_list))))
		return (NULL);
	glu[1] = '\0';
	while (*file)
	{
		tkn = ft_strdup("token=");
		while (ft_char(*file))
		{
			glu[0] = *file;
			fre = tkn;
			tkn = ft_strjoin(tkn, glu);
			free(fre);
		}
		/*liste*/
	}
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
