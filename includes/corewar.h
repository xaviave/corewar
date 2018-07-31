/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   corewar.h                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/19 13:50:45 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/24 20:58:52 by tduverge    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef _COREWAR_H
# define _COREWAR_H

# include "op.h"
# include "fcntl.h"
# include "../libft/header/libft.h"
# include <ncurses.h>

/*
 * STRUCTURES
 */

typedef struct		s_graph
{
	void			*win_ptr;
	void			*mlx_ptr;
	int				width;
	int				heigth;
}					t_graph;

typedef struct		s_champ
{
	int				id;
	char			name[PROG_NAME_LENGTH + 1];
	char			comment[COMMENT_LENGTH + 1];
	char			prog[CHAMP_MAX_SIZE];
	int				prog_size;
	int				number;
	void			*reg;
	unsigned		carry:1;
	int				live;
	int				cycle;
	int				pc;
	char			next_instru;
	struct s_champ	*next;
}					t_champ;

typedef struct		s_arg
{
	char			name[MAX_PLAYERS][PROG_NAME_LENGTH + 1];
	char			*champ_path[MAX_PLAYERS];
	int				champ_number[MAX_PLAYERS];
	int				nb_players;
}					t_arg;

typedef struct		s_mem
{
	int				id;
	unsigned char	*memory;
	unsigned char	*map;
	int				dump;
	int				last_live;
	t_graph			*img;
	int				call_live;
	int				c;
	int				c_todie;
	int				speed;
}					t_mem;

/*
 * STATIC COULEUR
 */

static char			color[4][12] = {GRN, RED, BLUE, PINK};

/*
 * FONCTIONS INITIALISATION
 */

void				init_window(t_mem *mem, t_champ *list);

void				init_champ(t_champ **champ, t_arg *args);
void				generate_memory(t_champ **list, t_mem *aff);
int					check_cor(int ac, char **av);
int					parse_arg(int ac, char **av, t_arg *args, t_mem *aff);
int					check_cor(int ac, char **av);

/*
 * FONCTIONS LECTURE ET ECRITURE
 */

void				print_mem(t_mem *mem, t_champ *list);
void				print_dump(t_mem *mem, t_champ *list);
void				write_reg(t_champ *champ, int nb_of_reg, int nb_to_write);
int					give_reg(t_champ *champ, int number);
unsigned int		recup_indirect4x(t_mem *mem, t_champ *champ, int start);
unsigned int		recup_indirect2x(t_mem *mem, t_champ *champ, int start);
unsigned int		recup_indirect4(t_mem *mem, t_champ *champ, int start);
unsigned int		recup_indirect2(t_mem *mem, t_champ *champ, int start);
unsigned int		recup_direct4(t_mem *mem, t_champ *champ, int start);
unsigned int		recup_direct2(t_mem *mem, t_champ *champ, int start);
unsigned char		recup_octet(t_mem *mem, t_champ *champ, int n);
int					mod_pc(t_champ *tmp, t_champ *list, t_mem *mem, int nu);

/*
 * FONCTIONS VRAC
 */

int					lets_go(t_champ **l, t_mem *m, t_arg *a);
int					lets_dump(t_champ **l, t_mem *m, t_arg *a);
int					list_len(t_champ *list);
int					ft_error2(char code, t_champ *tmp, int ret, int nu);
int					ft_error4(char code, t_champ *tmp, int ret, int nu);
void				check_cycle(t_champ **list, t_mem *mem, int c, t_arg *args);
int					check_live(t_champ **list);

/*
 * FONCTIONS UPCODE
 */

int		ft_live(t_champ *tmp, t_champ **list, t_mem *mem, t_arg *arg);
int		ft_ld(t_champ *tmp, t_champ **list, t_mem *mem, t_arg *arg);
int		ft_st(t_champ *tmp, t_champ **list, t_mem *mem, t_arg *arg);
int		ft_add(t_champ *tmp, t_champ **list, t_mem *mem, t_arg *arg);
int		ft_sub(t_champ *tmp, t_champ **list, t_mem *mem, t_arg *arg);
int		ft_and(t_champ *tmp, t_champ **list, t_mem *mem, t_arg *arg);
int		ft_or(t_champ *tmp, t_champ **list, t_mem *mem, t_arg *arg);
int		ft_xor(t_champ *tmp, t_champ **list, t_mem *mem, t_arg *arg);
int		ft_zjmp(t_champ *tmp, t_champ **list, t_mem *mem, t_arg *arg);
int		ft_ldi(t_champ *tmp, t_champ **list, t_mem *mem, t_arg *arg);
int		ft_sti(t_champ *tmp, t_champ **list, t_mem *mem, t_arg *arg);
int		ft_fork(t_champ *tmp, t_champ **list, t_mem *mem, t_arg *arg);
int		ft_lld(t_champ *tmp, t_champ **list, t_mem *mem, t_arg *arg);
int		ft_lldi(t_champ *tmp, t_champ **list, t_mem *mem, t_arg *arg);
int		ft_lfork(t_champ *tmp, t_champ **list, t_mem *mem, t_arg *arg);
int		ft_aff(t_champ *tmp, t_champ **list, t_mem *mem, t_arg *arg);

/*
**   KEY
*/

# define KEY_1 49
# define KEY_2 50
# define KEY_3 51
# define KEY_4 52
# define KEY_5 53
# define KEY_6 54
# define KEY_7 55
# define KEY_8 56
# define KEY_9 57
# define KEY_0 48
# define KEY_A 97
# define KEY_B 98
# define KEY_C 99
# define KEY_D 100
# define KEY_E 101
# define KEY_F 102
# define KEY_G 103
# define KEY_H 104
# define KEY_I 105
# define KEY_J 106
# define KEY_K 107
# define KEY_L 108
# define KEY_M 109
# define KEY_N 110
# define KEY_O 111
# define KEY_P 112
# define KEY_Q 113
# define KEY_R 114
# define KEY_S 115
# define KEY_T 116
# define KEY_U 117
# define KEY_V 118
# define KEY_W 119
# define KEY_X 120
# define KEY_Y 121
# define KEY_Z 122
# define KEY_SPACE 32

#endif
