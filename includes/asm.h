/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   asm.h                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lotoussa <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/23 14:22:31 by lotoussa     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/23 20:32:06 by lotoussa    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "../libft/header/libft.h"
# include "op.h"

# define _ARG argv[argc - 1]
# define _USAGE "[-a] <sourcefile.s>\n    -a : Instead of creating a .cor \
file, outputs a stripped and annotated version of the code to the standard \
output\n"
# define _LAB 1
# define _INS 2
# define _PAR 3
# define _SEP 4
# define _DIR 301
# define _IND 302
# define _REG 303

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
	int				type;
	int				par_type;
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
int					ft_check_detail(t_list **list);
int					ft_check_label_char(char *tkn, t_list *tmp);
int					ft_check_par_alone(char *tkn, t_list *tmp, t_list **list);
int					ft_while_digit(char *s);
char				*ft_name_file(int argc, char **argv);
int					ft_check_nb_ins_line(t_list *tmp, t_list **list);
int					ft_check_nb_ins_par(t_list *tmp);

#endif
