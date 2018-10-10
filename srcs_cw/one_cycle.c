/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   one_cycle.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tduverge <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/22 16:25:53 by tduverge     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/05 13:26:44 by tduverge    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/corewar.h"

static void		save_instru(t_mem *mem, t_champ *tmp)
{
	if (*(mem->memory + tmp->pc) > 16 || *(mem->memory + tmp->pc) == 0)
	{
		tmp->pc = mod_pc(tmp, 1);
		tmp->cycle++;
		return ;
	}
	tmp->next_instru = mem->memory[tmp->pc];
	tmp->cycle += mem->times[tmp->next_instru - 1] - 1;
}

static void		check_cycle(t_champ **list, t_mem *mem, int c, t_arg *args)
{
	t_champ		*tmp;
	int			carry;

	tmp = *list;
	while (tmp)
	{
		if (tmp->cycle == c && tmp->next_instru != -1)
		{
			carry = mem->instru[tmp->next_instru - 1](tmp, list, mem, args);
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

static void		del_maillon(t_champ **list, t_champ *before,
		t_champ *actual, t_champ *next)
{
	free(actual->reg);
	free(actual);
	if (before == NULL)
		*list = next;
	else
		before->next = next;
}

static void		check_live(t_champ **list)
{
	t_champ		*actual;
	t_champ		*before;
	t_champ		*next;

	before = NULL;
	actual = *list;
	while (actual)
	{
		next = actual->next;
		if (!actual->live)
			del_maillon(list, before, actual, next);
		else
		{
			actual->live = 0;
			before = actual;
		}
		actual = next;
	}
}

void			one_cycle(t_champ **list, t_mem *mem, t_arg *args, int *less)
{
	if (mem->c_before_check == 0)
	{
		check_live(list);
		if (mem->call_live >= NBR_LIVE || *less == MAX_CHECKS - 1)
		{
			mem->c_todie -= CYCLE_DELTA;
			*less = 0;
		}
		else
			(*less)++;
		mem->call_live = 0;
		if (mem->c_todie < 0)
			kill_them_all(list);
		mem->c_before_check = mem->c_todie;
		ft_bzero(mem->player_live, sizeof(int) * MAX_PLAYERS);
	}
	check_cycle(list, mem, mem->c, args);
	mem->c_before_check--;
	mem->c++;
}
