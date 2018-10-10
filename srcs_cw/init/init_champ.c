/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   init_champ.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xmoreau <xmoreau@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/20 17:30:33 by tduverge     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/05 12:35:18 by tduverge    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/corewar.h"

static t_champ	*create_champ(char *file, int size, t_champ **list, int number)
{
	t_champ		*champ;
	t_header	*tmp;

	tmp = (t_header*)file;
	champ = ft_memalloc(sizeof(t_champ));
	ft_memcpy(champ->name, &tmp->prog_name, PROG_NAME_LENGTH + 1);
	ft_memcpy(champ->comment, &tmp->comment, COMMENT_LENGTH + 1);
	ft_memcpy(champ->prog, file + sizeof(*tmp), size);
	champ->reg = ft_memalloc(REG_SIZE * REG_NUMBER);
	champ->prog_size = size;
	champ->number = number;
	champ->next_instru = -1;
	champ->next = *list;
	write_reg(champ, 1, -champ->number);
	return (champ);
}

static char		*recup_file(char *path, int *file_size)
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
		file = ft_memalloc((*file_size) + ret);
		if (tmp)
			ft_memcpy(file, tmp, (*file_size));
		ft_memcpy(file + (*file_size), line, ret);
		(*file_size) += ret;
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

static int		check_prog_size(char *file, int file_size)
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
	if (real_prog_size <= CHAMP_MAX_SIZE
			&& real_prog_size + (int)sizeof(t_header) == file_size)
		return (real_prog_size);
	return (0);
}

int				init_champ(t_champ **list, t_arg *args)
{
	int		i;
	int		file_size;
	char	*file;
	int		prog_size;

	i = -1;
	while (++i < args->nb_players)
	{
		file_size = 0;
		file = recup_file(args->champ_path[i], &file_size);
		if (!file || file_size < (int)sizeof(t_header) || !check_magic(file) ||
				!(prog_size = check_prog_size(file, file_size)))
		{
			if (file)
				ft_strdel(&file);
			return (-i - 1);
		}
		*list = create_champ(file, prog_size, list, i + 1);
		ft_memcpy(args->name[i], (*list)->name, PROG_NAME_LENGTH + 1);
		ft_strdel(&file);
	}
	return (0);
}
