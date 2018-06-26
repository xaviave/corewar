/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   corewar.h                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/19 13:50:45 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/26 13:50:05 by xamartin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef _COREWAR_H
# define _COREWAR_H

# include "op.h"
# include "fcntl.h"
# include "../libft/header/libft.h"

typedef struct		s_champ
{
	char			name[PROG_NAME_LENGTH + 1];
	char			comment[COMMENT_LENGTH + 1];
	char			prog[CHAMP_MAX_SIZE];
	int				prog_size;
	int				number;
	void			*reg;
	void			*pc;
	char			carry;
	struct s_champ	*next;
}					t_champ;

typedef struct		s_arg
{
	char			*champ_path[MAX_PLAYERS];
	int				champ_number[MAX_PLAYERS];
	int				nb_players;
	int				dump;
}					t_arg;

void				init_champ(t_champ **champ, t_arg *args);
void				write_reg(t_champ *champ, int nb_of_reg, int nb_to_write);
int					give_reg(t_champ *champ, int number);
char				*generate_memory(t_champ **list);

#endif
