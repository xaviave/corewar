/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main_cw.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/19 14:58:22 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/23 19:11:19 by tduverge    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/corewar.h"

static void		you_are_null(t_champ **list, t_mem *mem)
{
	*list = NULL;
	mem->memory = NULL;
	mem->map = NULL;
}

static int		introduce(t_champ *list, t_arg *args)
{
	int			i;
	int			j;
	t_champ		*tmp;

	tmp = list;
	ft_printf("Introducing contestants...\n");
	i = args->nb_players;
	while (i)
	{
		j = i - 1;
		tmp = list;
		while (j)
		{
			tmp = tmp->next;
			j--;
		}
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
				tmp->number, tmp->prog_size, tmp->name, tmp->comment);
		i--;
	}
	return (1);
}

static int		game_over(t_champ **list, t_mem *mem)
{
	if (mem->memory)
		free(mem->memory);
	if (mem->map)
		free(mem->map);
	kill_them_all(list);
	return (0);
}

int		main(int ac, char **av)
{
	t_champ	*list;
	t_arg	args;
	t_mem	mem;

	you_are_null(&list, &mem);
	if (all_init_is_love(&list, &args, ac, av))
		return (game_over(&list, &mem));
	generate_memory(&list, &mem, &args);
	if (args.graph == 1)
		lets_graph(&list, &mem, &args);
	else if (introduce(list, &args) && args.dump == -1)
		lets_go(&list, &mem, &args);
	else
		lets_dump(&list, &mem, &args);
	if (args.graph == -1 && args.dump == -1)
		ft_printf("Contestant %d, \"%s\", has won !\n",
				mem.last_live, args.name[mem.last_live - 1]);
	return (game_over(&list, &mem));
}
