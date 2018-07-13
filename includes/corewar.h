/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   corewar.h                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/19 13:50:45 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/13 16:26:28 by tduverge    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef _COREWAR_H
# define _COREWAR_H

# include "op.h"
# include "fcntl.h"
# include "../libft/header/libft.h"

/*
 * STRUCTURES
 */

typedef struct		s_champ
{
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
	unsigned char	*memory;
	unsigned char	*map;
	int				dump;
	int				last_live;
}					t_mem;

/*
 * STATIC COULEUR
 */

static char			color[4][12] = {GRN, RED, BLUE, PINK};

/*
 * FONCTIONS INITIALISATION
 */

void				init_champ(t_champ **champ, t_arg *args);
void				generate_memory(t_champ **list, t_mem *aff);
int					check_cor(int ac, char **av);
int					parse_arg(int ac, char **av, t_arg *args, t_mem *aff);
int					check_cor(int ac, char **av);

/*
 * FONCTIONS LECTURE ET ECRITURE
 */

void				print_mem(t_mem *mem);
void				write_reg(t_champ *champ, int nb_of_reg, int nb_to_write);
int					give_reg(t_champ *champ, int number);
unsigned int		recup_indirect4x(t_mem *mem, t_champ *champ, 
		unsigned int start);
unsigned int		recup_indirect2x(t_mem *mem, t_champ *champ, 
		unsigned int start);
unsigned int		recup_indirect4(t_mem *mem, t_champ *champ, 
		unsigned int start);
unsigned int		recup_indirect2(t_mem *mem, t_champ *champ, 
		unsigned int start);
unsigned int		recup_direct4(t_mem *mem, t_champ *champ, 
		unsigned int start);
unsigned int		recup_direct2(t_mem *mem, t_champ *champ, 
		unsigned int start);
unsigned char		recup_octet(t_mem *mem, t_champ *champ, 
		unsigned int n);

/*
 * FONCTIONS VRAC
 */

int					lets_go(t_champ **l, t_mem *m, t_arg *a);
int					lets_dump(t_champ **l, t_mem *m, t_arg *a);
int					list_len(t_champ *list);

/*
 * FONCTIONS UPCODE
 */

int		ft_live(t_champ *tmp, t_mem *mem, t_arg *arg);
int		ft_ld(t_champ *tmp, t_mem *mem, t_arg *arg);
int		ft_st(t_champ *tmp, t_mem *mem, t_arg *arg);
int		ft_add(t_champ *tmp, t_mem *mem, t_arg *arg);
int		ft_sub(t_champ *tmp, t_mem *mem, t_arg *arg);
int		ft_and(t_champ *tmp, t_mem *mem, t_arg *arg);
int		ft_or(t_champ *tmp, t_mem *mem, t_arg *arg);
int		ft_xor(t_champ *tmp, t_mem *mem, t_arg *arg);
int		ft_zjump(t_champ *tmp, t_mem *mem, t_arg *arg);
int		ft_ldi(t_champ *tmp, t_mem *mem, t_arg *arg);
int		ft_sti(t_champ *tmp, t_mem *mem, t_arg *arg);
int		ft_fork(t_champ *tmp, t_mem *mem, t_arg *arg);
int		ft_lld(t_champ *tmp, t_mem *mem, t_arg *arg);
int		ft_lldi(t_champ *tmp, t_mem *mem, t_arg *arg);
int		ft_lfork(t_champ *tmp, t_mem *mem, t_arg *arg);
int		ft_aff(t_champ *tmp, t_mem *mem, t_arg *arg);

#endif
