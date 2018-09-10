/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   asm.h                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lotoussa <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/23 14:22:31 by lotoussa     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/10 21:43:15 by lotoussa    ###    #+. /#+    ###.fr     */
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
# define CMP ft_strcmp

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
	int				lab;
	int				size;
}					t_compl;

char				*ft_first(int argc, char **argv);
t_all				ft_parsing(char **file);
int					ft_suite_parsing(char **file, t_all *a);
int					ft_third(char **argv, int argc, t_all *a);
int					ft_free_things(char *s1, char **s2);
int					ft_free_base(t_base *base);
char				*ft_extract_comment(char *line);
int					ft_check(t_all *a);
int					ft_increment_tkn(char **tkn, int i, int *l);
int					ft_increment_tkn_second(char **tkn, int i, int *l);
int					ft_check_detail(t_list **list);
int					ft_check_label_char(char *tkn, t_list *tmp);
int					ft_check_par_alone(char *tkn, t_list *tmp, t_list **list);
int					ft_while_digit(char *s);
char				*ft_name_file(int argc, char **argv);
int					ft_check_nb_ins_line(t_list *tmp, t_list **list);
int					ft_check_nb_ins_par(t_list *tmp);
int					ft_check_ins_type_par(t_list *tmp, char *tkn);
int					ft_nb_par_u(t_list *tmp);
int					ft_nb_par_ttu(t_list *tmp);
int					ft_nb_par_uuu(t_list *tmp);
int					ft_nb_par_tdu(t_list *tmp);
int					ft_nb_par_du(t_list *tmp);
int					ft_nb_par_ud(t_list *tmp);
int					ft_nb_par_utd(t_list *tmp);
int					ft_nb_par_aff(t_list *tmp);
int					ft_suite_tdu(t_list *tmp);
int					ft_count_size(t_list *list);
void				ft_count_size_ld_st(char *tkn, t_list **tmp, int *size);
int					ft_print_size(int size, int fd);
void				ft_print_zero(int fd, int i);
int					ft_anyway(t_all *a);
int					ft_bad_line(t_list **list);
char				*ft_strfjoin(char *s1, char *s2);
char				*ft_arg(int argc, char **argv);
int					ft_reform(t_all *a);
int					ft_bytecode(int fd, t_all *a);
int					ft_binary_to_hexa(int fd, char *tp);
t_list				*ft_byte_read_par(int fd, t_list *tmp);
int					ft_brut_label(t_all *a);
t_list				*ft_exception(int fd, t_list *tmp);
int					ft_create_size_tab(t_list **tmp);
void				ft_size_par_exception(int fd, int oct, t_list *tmp);
void				ft_memrev(char *ptr, size_t n);
int					ft_ins_one(t_list *tmp);
int					ft_ins_two(t_list *tmp);
int					ft_ins_three(t_list *tmp);
int					ft_ins_four(t_list *tmp);
int					ft_ins_five(t_list *tmp);
int					ft_attribute_last_lab(t_list **tmp);

#endif
