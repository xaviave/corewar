/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main_asm.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xmoreau <xmoreau@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/27 14:32:33 by xmoreau      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/04 15:50:09 by xmoreau     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/asm.h"

t_op			g_op_tab[16] =
{
	{"live", 1, {T_DIR}, 1, 10, 0, 0},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, 1, 0},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, 1, 0},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, 1, 0},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, 1, 0},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG},
		6, 6, 1, 0},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},
		7, 6, 1, 0},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},
		8, 6, 1, 0},
	{"zjmp", 1, {T_DIR}, 9, 20, 0, 1},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25, 1, 1},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25, 1, 1},
	{"fork", 1, {T_DIR}, 12, 800, 0, 1},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, 1, 0},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50, 1, 1},
	{"lfork", 1, {T_DIR}, 15, 1000, 0, 1},
	{"aff", 1, {T_REG}, 16, 2, 1, 0},
};

static int		check_argv(int ac, char **av, char *option, char **path)
{
	if (ac < 2)
		return (0);
	if (!ft_strcmp(av[1], "-a"))
	{
		*option = 1;
		*path = av[ac - 1];
		return (!ft_strcmp(av[ac - 1] + ft_strlen(av[ac - 1]) - 2, ".s") ?
				1 : 0);
	}
	*option = 0;
	*path = av[ac - 1];
	return (!ft_strcmp(av[ac - 1] + ft_strlen(av[ac - 1]) - 2, ".s") ? 1 : 0);
}

static char		*recup_file(char *path, int i)
{
	int			fd;
	char		line[50];
	char		*file;
	int			ret;
	char		*tmp;

	if ((fd = open(path, O_RDONLY)) < 0)
	{
		ft_printf("Can't read source file %s\n", path);
		return (NULL);
	}
	file = NULL;
	while ((ret = read(fd, &line, 50)) > 0)
	{
		tmp = file;
		if (!(file = ft_memalloc(i + ret + 1)))
			return (NULL);
		tmp ? ft_memcpy(file, tmp, i) : 0;
		if (!(ft_memcpy(file + i, line, ret)))
			return (NULL);
		i += ret;
		tmp ? free(tmp) : 0;
	}
	close(fd);
	return (file);
}

static	void	fill_header(t_header *header, t_cmd **cmd,
				t_label **label, t_infos *infos)
{
	t_cmd		*tmp;

	tmp = *cmd;
	header->prog_size = 0;
	while (tmp)
	{
		header->prog_size += (unsigned int)(tmp->size);
		tmp = tmp->next;
	}
	if (header->prog_size == 0)
	{
		ft_printf("The program is empty\n");
		free_all(*label, infos, cmd);
		exit(1);
	}
}

int				main(int ac, char **av)
{
	t_label		*label;
	t_cmd		*cmd;
	t_header	header;
	t_infos		infos;

	if (!check_argv(ac, av, &(infos.option), &(infos.path)))
		return (usage());
	label = NULL;
	cmd = NULL;
	if ((infos.file = recup_file(infos.path, 0)) == NULL)
		return (empty_file(infos.path));
	if ((infos.file = make_clean(infos.file)) == NULL)
		return (free_all(label, &infos, &cmd));
	check_pre_parsing(&infos.file);
	collect_header_and_labels(&label, &header, infos);
	collect_instructions(&label, &cmd, &infos);
	re_calculate_label_add(&label, cmd);
	fill_header(&header, &cmd, &label, &infos);
	convert_param(&cmd, &label);
	if (!infos.option)
		write_cor(cmd, &header, &infos);
	else
		write_output(cmd, label, &header);
	return (free_all(label, &infos, &cmd));
}
