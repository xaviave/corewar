#include "../includes/asm.h"

char		*ft_extract_comment(char *line)
{
	char	*new;
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	while (line[i - 1] != '\"')
		i++;
	new = ft_strdup(ft_strchr(line, '\"'));
	tmp = ft_memalloc(ft_strlen(new) - 2);
	i = 1;
	j = 0;
	while (new[i] != '\"')
		tmp[j++] = new[i++];
	tmp[j] = '\0';
	free(new);
	return (tmp);
}

char		*ft_help_extract(char *line)
{
	char	*label;
	char	*fre;
	char	*tmp;

	label = ft_strdup(line);
	tmp = label;
	label = ft_strjoin(label, "\n");
	free(tmp);
	return (label);
}

char		**ft_extract_label(char **sp)
{
	t_contain	ctn;
	char		**split;
	int			i;

	i = 0;
	ctn.buf = ft_strdup("\n");
	while (sp[i])
	{
		if (sp[i][ft_strlen(sp[i]) - 1] == ':')
		{
			ctn.tkn = ft_help_extract(sp[i]);
			ctn.fre = ctn.buf;
			ctn.buf = ft_strjoin(ctn.buf, ctn.tkn);
			free(ctn.fre);
			free(ctn.tkn);
		}
		i++;
	}
	if (!(split = ft_strsplit(ctn.buf, '\n')))
		return (NULL);
	free(ctn.buf);
	return (split);
}
