/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parsing.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tduverge <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/13 15:58:46 by tduverge     #+#   ##    ##    #+#       */
/*   Updated: 2018/08/22 14:24:00 by tduverge    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/corewar.h"

static int	end_parse_player(t_arg *args, int champ, char *temp[MAX_PLAYERS])
{
	int		i;
	int		j;

	j = 0;
	while (j < champ)
	{
		i = 0;
		while (args->champ_path[i])
			i++;
		args->champ_path[i] = temp[j];
		j++;
	}
	return (0);
}

static int	parse_player(int ac, char **av, t_arg *args, int i)
{
	int		champ;
	char	*temp[MAX_PLAYERS];

	champ = 0;
	ft_bzero(temp, MAX_PLAYERS * sizeof(char*));
	while (i < ac)
	{
		if (!ft_strcmp(av[i], "-n"))
		{
			if (i + 2 >= ac || !ft_strisdigit(av[i + 1])
					|| ft_strlen(av[i + 1]) > 9
					|| ft_atoi(av[i + 1]) > args->nb_players
					|| args->champ_path[ft_atoi(av[i + 1]) - 1])
				return (6);
			args->champ_path[ft_atoi(av[i + 1]) - 1] = av[i + 2];
			i += 2;
		}
		else
		{
			temp[champ] = av[i];
			champ++;
		}
		i++;
	}
	return (end_parse_player(args, champ, temp));
}

static int	parse_option(int ac, char **av, t_arg *args, int *i)
{
	while (*i < ac && av[*i][0] == '-')
	{
		if (!ft_strcmp(av[*i], "-dump"))
		{
			if (*i + 1 == ac || !ft_strisdigit(av[*i + 1])
					|| ft_strlen(av[*i + 1]) > 9)
				return (4);
			args->dump = ft_atoi(av[*i + 1]);
			(*i)++;
		}
		else if (!ft_strcmp(av[*i], "-graph"))
			args->graph = 1;
		else if (!ft_strcmp(av[*i], "-aff"))
			args->aff = 1;
		else if (!ft_strcmp(av[*i], "-n"))
			break ;
		else if (ft_strcmp(av[*i], "-help"))
			return (5);
		(*i)++;
	}
	return (0);
}

int			parse_arg(int ac, char **av, t_arg *args)
{
	int		i;
	int		error;

	i = 1;
	args->dump = -1;
	args->graph = -1;
	args->aff = -1;
	if ((error = parse_option(ac, av, args, &i)))
		return (error);
	ft_bzero(args->champ_path, MAX_PLAYERS * sizeof(char*));
	return (parse_player(ac, av, args, i));
}
