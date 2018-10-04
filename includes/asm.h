/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   asm.h                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xmoreau <xmoreau@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/23 14:22:31 by lotoussa     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/04 16:49:38 by xmoreau     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "../libft/header/libft.h"
# include "op.h"
# include <fcntl.h>

/*
** STRUCTURES
*/

typedef	struct		s_control
{
	int				name;
	int				comment;
	int				label;
	int				nb_param;
	int				coma;
	char			opcode;
}					t_control;

typedef struct		s_label
{
	char			*name;
	int				add;
	struct s_label	*next;
}					t_label;

typedef struct		s_cmd
{
	unsigned char	opcode;
	unsigned char	bytecode;
	int				add;
	char			size;
	char			*param[3];
	unsigned char	*byte_param[3];
	int				size_param[3];
	long			value_param[3];
	struct s_cmd	*next;
}					t_cmd;

typedef struct		s_op
{
	char			*name;
	int				nb_arg;
	int				arg[3];
	char			opcode;
	int				time;
	char			codage;
	char			dir_size;
}					t_op;

typedef struct		s_infos
{
	char			*path;
	char			*file;
	char			option;
}					t_infos;

typedef struct		s_stock
{
	t_label			*lab;
	t_label			**label;
	t_infos			*inf;
}					t_stock;

t_op	g_op_tab[16];

# define STOP_SIGN " \t\n"
# define SPLIT " \t,"

/*
** CHECKER
*/

void				check_pre_parsing(char **file);
void				error_check(int err);
int					check_name_comment(char **tab, t_control *control);
int					check_for_quote(char *file);
void				init_control(t_control *control);
char				get_opcode(char *s);
int					check_line_composition(char *file, t_control *control);
int					analyse_line(char *line, t_control *control, char **tab);
int					check_arg(char *arg, int type);
int					while_digit(char *s);
char				**ft_strsplit_modif(char const *s, char c);

/*
** BAD_USAGE
*/

int					usage(void);
int					empty_file(char *path);
int					finish_with_newline(char *file);
int					has_instruction(char *file);

/*
** COLLECT
*/

void				collect_header_and_labels(t_label **label,
		t_header *header, t_infos infos);
int					collect_name(t_header *header, char *file, int i);
int					collect_comment(t_header *header, char *file, int i);
int					collect_label(t_label **label, char *file, int i);
void				collect_instructions(t_label **label, t_cmd **cmd,
		t_infos *infos);

/*
** RECORD_CONVERT_CMD
*/

int					new_cmd(t_cmd **cmd, char **tab, int j, t_stock *stock);
char				get_bytecode(char **tab, int j, t_cmd *new);
int					record_arg(char *s, int pnb, t_stock *stock, t_cmd **new);
void				get_size_and_adress(t_cmd **cmd, t_cmd **created,
		t_stock *stock);
void				error_instru(t_cmd **cmd, int err, t_stock *stock,
		char **instru);
char				*make_clean(char *file);
void				calcul_size(t_cmd **created);
void				re_calculate_label_add(t_label **label, t_cmd *cmd);
void				convert_param(t_cmd **cmd, t_label **label);

/*
** WRITE
*/

void				write_output(t_cmd *cmd, t_label *label, t_header *header);
int					write_cor(t_cmd *cmd, t_header *header, t_infos *infos);

/*
** TOOLS
*/

int					start_by(char *str, char *name);
int					to_the_next_char(char *str, int i);
int					to_the_next_line(char *str, int i);
void				give_coline(char *str, int i, int *tab);
char				*get_next_word(char *file, int i, char separator);
char				**multi_split(const char *str, char *c);
long				ft_long_atoi(const char *str);

/*
** TOOLS/FREE ALL
*/

int					free_all(t_label *label, t_infos *infos, t_cmd **cmd);
t_label				*free_label(t_label *label);
void				free_tab(char **tab);
t_cmd				*free_cmd(t_cmd *cmd);

#endif
