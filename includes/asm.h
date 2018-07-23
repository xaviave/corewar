/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   asm.h                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lotoussa <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/23 14:22:31 by lotoussa     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/23 15:15:42 by lotoussa    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "../libft/header/libft.h"

# define _ARG argv[argc - 1]
# define _USAGE "[-a] <sourcefile.s>\n    -a : Instead of creating a .cor \
file, outputs a stripped and annotated version of the code to the standard \
output\n"

typedef struct		s_contain
{
	char			*tkn;
	char			*fre;
	char			*buf;
}					t_contain;

typedef struct		s_base
{
	char			*name;
	char			*comment;
	char			**tkn;
}					t_base;

typedef struct		s_all
{
	t_base			base;
	int				file_size;
	char			*file_name;
	t_list			*t;
}					t_all;

typedef struct		s_compl
{
	char			*tkn;
	int				line;
}					t_compl;

char				*ft_first(int argc, char **argv);
t_all				ft_parsing(char **file);
int					ft_suite_parsing(char **file, char **split, t_all *a);
int					ft_third(char **argv, int argc, t_all *a);
int					ft_free_things(char *s1, char **s2);
int					ft_free_base(t_base *base);
char				*ft_extract_comment(char *line);
int					ft_check(t_all *a);
int					ft_increment_tkn(char **tkn, int i, int *l);

#endif
