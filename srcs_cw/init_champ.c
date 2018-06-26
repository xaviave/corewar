/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   corewar.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tduverge <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/20 17:30:33 by tduverge     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/26 13:13:16 by xamartin    ###    #+. /#+    ###.fr     */
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

t_champ		*create_champ(char *file, int prog_size, t_champ **list)
{
	t_champ		*champ;

	champ = ft_memalloc(sizeof(t_champ));
	ft_memcpy(champ->name, file + 4, PROG_NAME_LENGTH + 1);
	ft_memcpy(champ->comment, file + 140, COMMENT_LENGTH + 1);
	ft_memcpy(champ->prog, file + 2192, prog_size);
	champ->reg = ft_memalloc(REG_SIZE * REG_NUMBER);
	champ->prog_size = prog_size;
	champ->carry = 1;
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
		file = ft_memalloc(i + ret + 1);
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
		return (real_prog_size);
	return (0);
}

void		error(char *file, t_champ **list)
{
	t_champ		*champ;
	t_champ		*tmp;

	if (!(file))
		ft_putstr("FILE INVALID\n");
	else if (!check_magic(file))
		ft_putstr("MAGIC INVALID\n");
	else if (!check_prog_size(file))
		ft_putstr("CHAMP TO BIG\n");
	free(file);
	champ = *list;
	while (champ)
	{
		tmp = champ;
		champ = champ->next;
		free(tmp->reg);
		free(tmp);
	}
}

void		init_champ(t_champ **list, t_arg *args)
{
	int		i;
	char	*file;
	int		prog_size;

	i = -1;
	while (++i < args->nb_players)
	{
		file = recup_file(args->champ_path[i], 0);
		if (!file || !check_magic(file) || !(prog_size = check_prog_size(file)))
			return (error(file, list));
		*list = create_champ(file, prog_size, list);
		(*list)->number = i + 1;
		write_reg(*list, 1, (*list)->number);
		ft_strdel(&file);
	}
	t_champ *test;
	test = *list;
	while (test)
	{
		ft_printf("name = %s | comment = %s | number = %d\n", test->name, test->comment, test->number);
		test = test->next;
	}
}
