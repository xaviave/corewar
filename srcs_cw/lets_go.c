/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lets_go.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tduverge <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/09 16:14:43 by tduverge     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/12 15:49:26 by tduverge    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/corewar.h"

static int			(*instru[1])(t_champ *tmp, t_mem *mem, t_arg *args) = {
	&ft_live};

static	int		times[16] = {10, 5, 5, 10, 10, 6, 6, 6, 20, 25, 25, 800, 10,
	50, 1000, 2};

/*static int			(*instru[16])(t_champ *tmp, t_mem *mem, t_arg *args) = {
	&ft_live, &ft_ld, &ft_st, &ft_add, &ft_sub, &ft_and, &ft_or, &ft_xor,
	&ft_zjump, &ft_ldi, &ft_sti, &ft_fork, &ft_lld, &ft_lldi, &ft_lfork,
	&ft_aff};*/

int		ft_live(t_champ *tmp, t_mem *mem, t_arg *args)
{
	int	name;

	name = 0;
	ft_memcpy(&name, tmp->next_instru + 4, 1);
	ft_memcpy((char*)&name + 1, tmp->next_instru + 3, 1);
	ft_memcpy((char*)&name + 2, tmp->next_instru + 2, 1);
	ft_memcpy((char*)&name + 3, tmp->next_instru + 1, 1);
	name = -name;
	if (name > args->nb_players || name <= 0)
		return (-1);
	mem->last_live = name;
	ft_printf(YEL"un processus dit que le joueur %d(%s) est en vie\n"RESET, name,
			args->name[name - 1]);
	tmp->live++;
	tmp->pc = (5 + tmp->pc) % MEM_SIZE;
	return (-1);
}

void	save_instru(t_mem *mem, t_champ *tmp)
{
	if (*(mem->memory + tmp->pc) > 16 || *(mem->memory + tmp->pc) == 0)
	{
		tmp->pc = (tmp->pc + 1) % MEM_SIZE;
		tmp->cycle++;
		return ;
	}
	ft_memcpy(tmp->next_instru, mem->memory + tmp->pc, 1);
	ft_memcpy(tmp->next_instru + 1, mem->memory + (tmp->pc + 1) % MEM_SIZE, 1);
	ft_memcpy(tmp->next_instru + 2, mem->memory + (tmp->pc + 2) % MEM_SIZE, 1);
	ft_memcpy(tmp->next_instru + 3, mem->memory + (tmp->pc + 3) % MEM_SIZE, 1);
	ft_memcpy(tmp->next_instru + 4, mem->memory + (tmp->pc + 4) % MEM_SIZE, 1);
	ft_memcpy(tmp->next_instru + 5, mem->memory + (tmp->pc + 5) % MEM_SIZE, 1);
	ft_memcpy(tmp->next_instru + 6, mem->memory + (tmp->pc + 6) % MEM_SIZE, 1);
	ft_memcpy(tmp->next_instru + 7, mem->memory + (tmp->pc + 7) % MEM_SIZE, 1);
	ft_memcpy(tmp->next_instru + 8, mem->memory + (tmp->pc + 8) % MEM_SIZE, 1);
	ft_memcpy(tmp->next_instru + 9, mem->memory + (tmp->pc + 9) % MEM_SIZE, 1);
	tmp->cycle += times[tmp->next_instru[0] - 1] - 1;
}

void	check_cycle(t_champ *list, t_mem *mem, int c, t_arg *args)
{
	t_champ		*tmp;
	int			carry;

	tmp = list;
	while (tmp)
	{
		if (tmp->cycle == c && tmp->next_instru[0] != -1)
		{
			carry = instru[tmp->next_instru[0] - 1](tmp, mem, args);
			tmp->next_instru[0] = -1;
			tmp->cycle++;
			if (carry >= 0)
				tmp->carry = carry;
		}
		else if (tmp->cycle == c && tmp->next_instru[0] == -1)
			save_instru(mem, tmp);
		tmp = tmp->next;
	}
}

int		check_live(t_champ **list)
{
	int			live;
	t_champ		*tmp;
	t_champ		*before;

	live = 0;
	tmp = *list;
	before = NULL;
	while (tmp)
	{
		if (!tmp->live)
		{
			if (tmp == *list)
				*list = tmp->next;
			else
				before->next = tmp->next;
			free(tmp->reg);
			free(tmp);
		}
		else
			before = tmp;
		if (tmp->live > NBR_LIVE)
			live = 1;
		tmp->live = 0;
		if (before)
			tmp = before->next;
		else
			tmp = *list;
	}
	return (live ? -1 : list_len(*list));
}

int		lets_go(t_champ **list, t_mem *mem, t_arg *args)
{
	int		c;
	int		c_todie;
	int		tmp;
	int		less;
	int		very_less;

	c = 0;
	c_todie = CYCLE_TO_DIE;
	tmp = c_todie;
			int	i = -1;
			while (++i < MEM_SIZE)
		{
			if (i)
			{
				if (i % 64 == 0)
					ft_printf("\n");
			}
			if (mem->map[i] == 1)
				ft_printf(RED"");
			if (mem->map[i] == 2)
				ft_printf(BLUE"");
			ft_printf("%02x "RESET, mem->memory[i]);
		}
		ft_printf("\n");
	while (1)
	{
		check_cycle(*list, mem, c, args);
		c_todie--;
		if (c_todie == 0)
		{
			if (!(less = check_live(list)))
				break;
			if (less == -1 || very_less == MAX_CHECKS)
			{
				c_todie = tmp - CYCLE_DELTA;
				tmp = c_todie;
				very_less = 0;
			}
			else
			{
				very_less++;
				c_todie = tmp;
			}
		}
		c++;
	}
	return (0);
}
