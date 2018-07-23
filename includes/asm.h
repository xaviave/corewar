/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   asm.h                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xmoreau <xmoreau@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/20 17:53:02 by xmoreau      #+#   ##    ##    #+#       */
<<<<<<< HEAD
/*   Updated: 2018/07/22 21:09:25 by lotoussa    ###    #+. /#+    ###.fr     */
=======
<<<<<<< HEAD
/*   Updated: 2018/07/20 15:45:35 by tduverge    ###    #+. /#+    ###.fr     */
=======
/*   Updated: 2018/07/22 20:49:00 by lotoussa    ###    #+. /#+    ###.fr     */
>>>>>>> f2bee9febe0f3d3618c45295a311fa9b8bf7ca00
>>>>>>> 8e5019c0dc54b6ebe9f8526bbd325b8641f3c036
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
