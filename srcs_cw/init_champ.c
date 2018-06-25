/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   corewar.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tduverge <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/20 17:30:33 by tduverge     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/25 18:47:12 by tduverge    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/corewar.h"

void		add_champ(t_champ **start, t_champ *to_add)
{
	if (*start == NULL)
	{
		*start = to_add;
		return ;
	}
	to_add->next = *start;
	*start = to_add;
}

void		add_number(t_arg *args, t_champ **list, t_champ **champ)
{
	int		nb;

	nb = 0;

	if (!*list && args->champ_number[0] != -1)
		write_reg(champ, 1, args->champ_number[0]);
	else if (!*list && args->champ_number[1] == -1)
		write_reg(champ, 1, 0);
	else if (!*list && args->champ_number[1] != -1)
		write_reg(champ, 1, args->champ_number[1] + 1);
	else if (*list && args->champ_number[1] != -1)
		write_reg(champ, 1, args->champ_number[1]);
	else if (*list && args->champ_number[0] == -1)
		write_reg(champ, 1, 1);
	else if (*list && args->champ_number[0] != -1)
		write_reg(champ, 1, args->champ_number[0] + 1);
}

t_champ		*create_champ(char *name, char *com, t_arg *args, t_champ **list)
{
	t_champ		*champ;

	champ = ft_memalloc(sizeof(t_champ));
	ft_memcpy(champ->name, name, PROG_NAME_LENGTH + 1);
	ft_memcpy(champ->comment, com, COMMENT_LENGTH + 1);
	champ->reg = ft_memalloc(REG_SIZE * REG_NUMBER);
	champ->pc = NULL;
	champ->carry = 1;
	champ->next = NULL;
	add_number(args, list, &champ);
	add_champ(list, champ);
	return (*list);
}

char		*recup_file(char *path, int i)
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

int			check_magic(char *file)
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

int			check_prog_size(char *file)
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
		return (1);
	return (0);
}

void		init_champ(t_champ **list, t_arg *args)
{
	int		i;
	char	*file;

	i = -1;
	while (++i < MAX_PLAYERS)
	{
		file = recup_file(args->champ_path[i], 0);
		if (!(file))
		{
			ft_putstr("FILE INVALID\n");
			return ;
		}
		if (!check_magic(file))
		{
			ft_putstr("MAGIC INVALID\n");
			return ;
		}
		if (!check_prog_size(file))
		{
			ft_putstr("CHAMP TO BIG\n");
			return ;
		}
		*list = create_champ(file + 4, file + 140, args, list);
		ft_strdel(&file);
	}
}
