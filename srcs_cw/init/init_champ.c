/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   corewar.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tduverge <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/20 17:30:33 by tduverge     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/23 18:07:34 by tduverge    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/corewar.h"

static t_champ	*create_champ(char *file, int size, t_champ **list, int number)
{
	t_champ		*champ;

	champ = ft_memalloc(sizeof(t_champ));
	ft_memcpy(champ->name, file + 4, PROG_NAME_LENGTH + 1);
	ft_memcpy(champ->comment, file + 140, COMMENT_LENGTH + 1);
	ft_memcpy(champ->prog, file + 2192, size);
	champ->reg = ft_memalloc(REG_SIZE * REG_NUMBER);
	champ->prog_size = size;
	champ->number = number;
	champ->next_instru = -1;
	champ->next = *list;
	write_reg(champ, 1, -champ->number);
	return (champ);
}

static char		*recup_file(char *path, int i)
{
	int		fd;
	char	line[50];
	char	*file;
	int		ret;
	char	*tmp;

	fd = open(path, O_RDONLY);
	file = NULL;
	while ((ret = read(fd, &line, 50)) > 0)
	{
		tmp = file;
		file = ft_memalloc(i + ret);
		if (tmp)
			ft_memcpy(file, tmp, i);
		ft_memcpy(file + i, line, ret);
		i += ret;
		if (tmp)
			free(tmp);
	}
	return (file);
}

static int		check_magic(char *file)
{
	long		magic;
	long		real_magic;
	int			i;

	i = 0;
	magic = 0;
	ft_memcpy(&magic, file, 4);
	real_magic = 0;
	while (i < 4)
	{
		real_magic += (((0xff << (8 * i)) & magic) >> 8 * i) << ((3 - i) * 8);
		i++;
	}
	if (real_magic == COREWAR_EXEC_MAGIC)
		return (1);
	return (0);
}

static int		check_prog_size(char *file)
{
	long	prog_size;
	long	real_prog_size;
	int		i;

	i = 0;
	prog_size = 0;
	real_prog_size = 0;
	ft_memcpy(&prog_size, file + 136, 4);
	while (i < 4)
	{
		real_prog_size += (((0xff << (8 * i)) & prog_size) >> 8 * i)
			<< ((3 - i) * 8);
		i++;
	}
	if (real_prog_size <= CHAMP_MAX_SIZE)
		return (real_prog_size);
	return (0);
}

int			init_champ(t_champ **list, t_arg *args)
{
	int		i;
	char	*file;
	int		prog_size;

	i = -1;
	while (++i < args->nb_players)
	{
		file = recup_file(args->champ_path[i], 0);
		if (!file || !check_magic(file) || !(prog_size = check_prog_size(file)))
			return (-i - 1);
		*list = create_champ(file, prog_size, list, i + 1);
		ft_memcpy(args->name[i],(*list)->name, PROG_NAME_LENGTH + 1);
		ft_strdel(&file);
	}
	return (0);
}
