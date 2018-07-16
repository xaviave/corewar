/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lets_go.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tduverge <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/09 16:14:43 by tduverge     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/16 23:39:44 by tduverge    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/corewar.h"

static int			(*instru[16])(t_champ *tmp, t_champ *list, t_mem *mem, t_arg *args) = {
	&ft_live, &ft_ld, &ft_st, &ft_add, &ft_sub, &ft_and, &ft_or, &ft_xor,
	&ft_zjmp, &ft_ldi, &ft_sti, &ft_fork, &ft_lld, &ft_lldi, &ft_lfork,
	&ft_aff};

static	int		times[16] = {10, 5, 5, 10, 10, 6, 6, 6, 20, 25, 25, 800, 10,
	50, 1000, 2};

void	save_instru(t_mem *mem, t_champ *tmp, t_champ *list)
{
	if (*(mem->memory + tmp->pc) > 16 || *(mem->memory + tmp->pc) == 0)
	{
		tmp->pc = mod_pc(tmp, list, mem, 1);
		//tmp->pc = (tmp->pc + 1) % MEM_SIZE;
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
			carry = instru[tmp->next_instru - 1](tmp, list, mem, args);
			tmp->next_instru = -1;
			tmp->cycle++;
			if (carry >= 0)
				tmp->carry = carry;
		}
		else if (tmp->cycle == c && tmp->next_instru == -1)
			save_instru(mem, tmp, list);
		tmp = tmp->next;
	}
}

void	del_maillon(t_champ **list, int n)
{
	t_champ		*tmp;
	t_champ		*before;

	tmp = *list;
	if (n == 0)
		*list = (*list)->next;
	else
	{
		while (n)
		{
			before = tmp;
			tmp = tmp->next;
			n--;
		}
		before->next = tmp->next;
	}
	free(tmp->reg);
	free(tmp);
}

int		check_live(t_champ **list)
{
	t_champ		*tmp;
	int			live;
	int			i;

	live = 0;
	tmp = *list;
	i = 0;
	while (tmp)
	{
		if (!tmp->live)
		{
			del_maillon(list, i);
			i--;
		}
		else
		{
			if (tmp->live > NBR_LIVE)
				live = -1;
			if (live != -1)
				live = 1;
			tmp->live = 0;
		}
		tmp = tmp->next;
		i++;
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
	very_less = 0;
	c_todie = CYCLE_TO_DIE;
	tmp = c_todie;
	print_mem(mem, *list);
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
	print_mem(mem, *list);
	return (0);
}
