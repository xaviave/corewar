/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main_cw.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/19 14:58:22 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2018/08/22 16:53:37 by tduverge    ###    #+. /#+    ###.fr     */
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

static int		put_help(void)
{
	ft_printf("Usage: /corewar [-aff] [-graph] [-dump nbr_cycles] ");
	ft_printf("[[-n number] champion1.cor]\n\n");
	ft_printf("#### CLASSIC MODE ############################################");
	ft_printf("#####################################\n");
	ft_printf("\n\tEnter between 2 and %d champions (file .cor)", MAX_PLAYERS);
	ft_printf(" create by the asm\n\n\t\t-aff   \t\t: ");
	ft_printf("use this option to see live and print output from \"aff\"\n");
	ft_printf("\n\t\t-n    N\t\t: ");
	ft_printf("Use this option to select the position of the next champion\n");
	ft_printf("\t\t       \t\t  ");
	ft_printf("Be careful, 2 champions can't have the same position\n");
	ft_printf("\t\t       \t\t  ");
	ft_printf("and N have to be between 1 and the number total of champions");
	ft_printf("\n\n#### DUMP MODE ###########################################");
	ft_printf("#########################################\n");
	ft_printf("\n\t\t-dump N\t\t: ");
	ft_printf("Use this option to print memory after N cycles then exists\n");
	ft_printf("\t\t       \t\t  This is compatible with -graph\n\n");
	ft_printf("#### GRAPH MODE ##############################################");
	ft_printf("#####################################\n");
	ft_printf("\n\t\t-graph\t\t: ");
	ft_printf("Use this option to enter in the wonderful world of graphism\n");
	ft_printf("\t\t       \t\t  This option disable -aff\n\n");
	return (0);
}

int				main(int ac, char **av)
{
	t_champ	*list;
	t_arg	args;
	t_mem	mem;

	if (ac == 1 || (ac == 2 && !ft_strcmp("-help", av[1])))
		return (put_help());
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
