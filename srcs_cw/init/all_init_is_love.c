#include "../../includes/corewar.h"

static int		put_usage(t_arg *args, int error)
{
	ft_printf("Usage: /corewar [-aff] [-graph] [-dump nbr_cycles] ");
	ft_printf("[[-n number] champion1.cor]\n");
	if (error == 1 || error == 2)
		ft_printf("\t>>> We need at least two champions to make a fight...");
	else if (error == 3)
		ft_printf("\t>>> We are not wild, not more than %d in a fight.",
				MAX_PLAYERS);
	else if (error == 4)
		ft_printf("\t>>> Stupid, \"-dump\" has to be followed by a number.");
	else if (error == 5)
		ft_printf("\t>>> Don't use illegal option, terrorist !");
	else if (error == 6)
		ft_printf("\t>>> \"-n\" has to be followed by a number AND a champion");
	else if (error < 0)
		ft_printf("\t>>> I don't think \"%s\" is a valid file.",
				args->champ_path[-(error + 1)]);
	ft_printf("\n");
	ft_printf("For more information you can use : \"./corewar -help\"\n");
	return (1);
}

int			all_init_is_love(t_champ **list, t_arg *args, int ac, char **av)
{
	int		error;

	if (ac < 3)
		return (put_usage(args, 1));
	else if ((args->nb_players = check_cor(ac, av)) < 2)
		return (put_usage(args, 2));
	else if (args->nb_players > MAX_PLAYERS)
		return (put_usage(args, 3));
	else if ((error = parse_arg(ac, av, args)))
		return (put_usage(args, error));
	else if ((error = init_champ(list, args)))
		return (put_usage(args, error));
	return (0);
}
