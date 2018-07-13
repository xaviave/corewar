/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lets_go.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tduverge <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/09 16:14:43 by tduverge     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/13 16:48:24 by tduverge    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/corewar.h"

static int			(*instru[2])(t_champ *tmp, t_mem *mem, t_arg *args) = {
	&ft_live, &ft_ld};

static	int		times[16] = {10, 5, 5, 10, 10, 6, 6, 6, 20, 25, 25, 800, 10,
	50, 1000, 2};

/*static int			(*instru[16])(t_champ *tmp, t_mem *mem, t_arg *args) = {
	&ft_live, &ft_ld, &ft_st, &ft_add, &ft_sub, &ft_and, &ft_or, &ft_xor,
	&ft_zjump, &ft_ldi, &ft_sti, &ft_fork, &ft_lld, &ft_lldi, &ft_lfork,
	&ft_aff};*/

void	save_instru(t_mem *mem, t_champ *tmp)
{
	if (*(mem->memory + tmp->pc) > 16 || *(mem->memory + tmp->pc) == 0)
	{
		tmp->pc = (tmp->pc + 1) % MEM_SIZE;
		tmp->cycle++;
		return ;
	}
	tmp->next_instru =  mem->memory[tmp->pc];
	tmp->cycle += times[tmp->next_instru - 1] - 1;
}

void	check_cycle(t_champ *list, t_mem *mem, int c, t_arg *args)
{
	t_champ		*tmp;
	int			carry;

	tmp = list;
	while (tmp)
	{
		if (tmp->cycle == c && tmp->next_instru != -1)
		{
			carry = instru[tmp->next_instru - 1](tmp, mem, args);
			tmp->next_instru = -1;
			tmp->cycle++;
			if (carry >= 0)
				tmp->carry = carry;
		}
		else if (tmp->cycle == c && tmp->next_instru == -1)
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
		{
			before = tmp;
			if (tmp->live > NBR_LIVE)
				live = -1;
			if (live != -1)
				live = 1;
			tmp->live = 0;
		}
		if (before)
			tmp = before->next;
		else
			tmp = *list;
	}
	return (live);
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
	print_mem(mem);
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
