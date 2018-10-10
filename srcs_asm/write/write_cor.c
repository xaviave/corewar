/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   write_cor.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xmoreau <xmoreau@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/26 20:39:08 by xmoreau      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/04 15:56:54 by xmoreau     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/asm.h"

static void			print_cmd(t_cmd *cmd, int fd)
{
	int				i;
	int				j;

	while (cmd != NULL)
	{
		write(fd, &cmd->opcode, 1);
		if (cmd->bytecode != 0)
			write(fd, &cmd->bytecode, 1);
		i = 0;
		while (i < 3)
		{
			j = 0;
			while (j < 4)
			{
				if (cmd->param[i] != NULL && j < cmd->size_param[i])
					write(fd, &(cmd->byte_param[i][j]), 1);
				j++;
			}
			i++;
		}
		cmd = cmd->next;
	}
}

static void			print_int(unsigned int nb, int fd)
{
	unsigned char	rev[4];
	int				i;

	i = 0;
	rev[3] = 0;
	rev[2] = 0;
	rev[1] = 0;
	rev[0] = 0;
	rev[3] = nb & 0xff;
	rev[2] = (nb & 0xff00) >> 8;
	rev[1] = (nb & 0xff0000) >> 16;
	rev[0] = (nb & 0xff000000) >> 24;
	while (i < 4)
	{
		write(fd, &rev[i], 1);
		i++;
	}
}

static void			write_foor(int fd)
{
	char *four;

	four = ft_memalloc(sizeof(char) * 4);
	write(fd, four, 4);
	ft_strdel(&four);
}

static void			write_header(int fd, t_header *header)
{
	print_int(header->magic, fd);
	write(fd, header->prog_name, PROG_NAME_LENGTH);
	write_foor(fd);
	print_int(header->prog_size, fd);
	write(fd, header->comment, COMMENT_LENGTH);
	write_foor(fd);
}

int					write_cor(t_cmd *cmd, t_header *header, t_infos *infos)
{
	int				fd;
	char			*path;
	char			*new_path;

	if (!(path = ft_strsub(infos->path, 0, ft_strlen(infos->path) - 2)))
		return (-1000);
	if (!(new_path = ft_strjoin(path, ".cor")))
		return (-1000);
	if ((fd = open(new_path, O_RDWR | O_CREAT |
	O_TRUNC, S_IRUSR | S_IWUSR)) < 0)
	{
		ft_strdel(&path);
		ft_strdel(&new_path);
		return (ft_printf("Could not create file."));
	}
	write_header(fd, header);
	print_cmd(cmd, fd);
	ft_printf("Writing output program to %s\n", new_path);
	ft_strdel(&path);
	ft_strdel(&new_path);
	close(fd);
	return (0);
}
