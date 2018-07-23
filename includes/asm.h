/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   asm.h                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xmoreau <xmoreau@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/20 17:53:02 by xmoreau      #+#   ##    ##    #+#       */
/*   Updated: 2018/07/22 21:09:25 by lotoussa    ###    #+. /#+    ###.fr     */
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

char				*ft_first(int argc, char **argv);
t_all				ft_parsing(char **file);
int					ft_suite_parsing(char **file, char **split, t_all *a);
int					ft_third(char **argv, int argc, t_all *a);
int					ft_free_things(char *s1, char **s2);
int					ft_free_base(t_base *base);
char				*ft_extract_comment(char *line);
int					ft_check(t_all *a);

#endif
