/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parsing.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tduverge <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/13 15:58:46 by tduverge     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/13 16:15:53 by tduverge    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/corewar.h"

int		parse_player(int ac, char **av, t_arg *args, int i)
{
	int		champ;
	char	*temp[MAX_PLAYERS];
	int		j;

	champ = 0;
	ft_bzero(temp, MAX_PLAYERS * sizeof(char*));
	while (i < ac)
	{
		if (!ft_strcmp(av[i], "-n"))
		{
			if (i + 2 >= ac || !ft_strisdigit(av[i + 1])
					|| ft_atoi(av[i + 1]) > args->nb_players
					|| args->champ_path[ft_atoi(av[i + 1]) - 1])
				return (0);
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
	j = 0;
	while (j < champ)
	{
		i = 0;
		while (args->champ_path[i])
			i++;
		args->champ_path[i] = temp[j];
		j++;;
	}
	return (1);
}

int		parse_option(int ac, char **av, t_arg *args, int *i)
{
	while (*i < ac && av[*i][0] == '-')
	{
		if (!ft_strcmp(av[*i], "-dump"))
		{
			if (*i + 1 == ac || !ft_strisdigit(av[*i + 1]))
				return (0);
			args->dump = ft_atoi(av[*i + 1]);
			*i += 2;
		}
		else if (!ft_strcmp(av[*i], "-graph"))
		{
			args->graph = 1;
			(*i)++;
		}
		else if (!ft_strcmp(av[*i], "-n"))
			break ;
		else
			return (0);
	}
	return (1);
}

int		parse_arg(int ac, char **av, t_arg *args, t_mem *aff)
{
	int		i;

	i = 1;
	args->dump = -1;
	args->graph = -1;
	if (!parse_option(ac, av, args, &i))
		return (0);
	ft_bzero(args->champ_path, MAX_PLAYERS * sizeof(char*));
	return (parse_player(ac, av, args, i));
}

int		check_cor(int ac, char **av)
{
	int	i;
	int	j;
	int	cor;

	cor = 0;
	i = 0;
	while (++i < ac)
	{
		j = ft_strlen(av[i]) - 1;
		if (j >= 3 && av[i][j] == 'r' && av[i][j - 1] == 'o'
				&& av[i][j - 2] == 'c' && av[i][j - 3]== '.')
			cor++;
	}
	return (cor);
}
