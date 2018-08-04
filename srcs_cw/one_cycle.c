#include "../includes/corewar.h"

static void		save_instru(t_mem *mem, t_champ *tmp)
{
	if (*(mem->memory + tmp->pc) > 16 || *(mem->memory + tmp->pc) == 0)
	{
		tmp->pc = mod_pc(tmp, 1);
		tmp->cycle++;
		return ;
	}
	tmp->next_instru =  mem->memory[tmp->pc];
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

static void		del_maillon(t_champ **list, int n)
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

static void		check_live(t_champ **list)
{
	t_champ		*tmp;
	t_champ		*tmp2;
	int			live;
	int			i;

	live = 0;
	tmp = *list;
	i = 0;
	while (tmp)
	{
		tmp2 = tmp->next;
		if (!tmp->live)
			del_maillon(list, i);
		else
		{
			tmp->live = 0;
			i++;
		}
		tmp = tmp2;;
	}
}

void			one_cycle(t_champ **list, t_mem *mem, t_arg *args, int *less)
{
	if (mem->c_before_check ==  0)
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
		ft_bzero(mem->player_live, MAX_PLAYERS * sizeof(int));
	}
	check_cycle(list, mem, mem->c, args);
	mem->c_before_check--;
	mem->c++;
}
