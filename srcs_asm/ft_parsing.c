#include "../includes/asm.h"

int			ft_char(char let)
{
	if (let == '.' || let == ' ' || let == '"' || let == '\n' || let == ','
		|| let == '\t')
		return (0);
	else
		return (1);
}

t_tkn		*ft_lexer(char *file)
{
	char	*tkn;
	char	glu[2];
	char	*fre;
	t_tkn	*list;
	t_tkn	*tmp;

	glu[1] = '\0';
	list = NULL;
	while (*file)
	{
		tkn = ft_strdup("token=");
		while (ft_char(*file))
		{
			glu[0] = *file++;
			fre = tkn;
			tkn = ft_strjoin(tkn, glu);
			free(fre);
		}
		if (!ft_strcmp(tkn, "token="))
		{
			fre = tkn;
			glu[0] = *file++;
			tkn = ft_strjoin(tkn, glu);
			free(fre);
		}
		if (!(tmp = ft_tknnew(tkn)))
			return (NULL);
		ft_tknpush(&list, tmp);
		free(tkn);
	}
	return (list);
}

int			ft_parsing(char *file)
{
	t_tkn		*list;

	if (!(list = ft_lexer(file)))
	{
		free(file);
		exit(1);
	}
	return (0);
}
