/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   writing_output.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xmoreau <xmoreau@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/26 18:21:56 by xmoreau      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/04 15:56:54 by xmoreau     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/asm.h"

static void		print_intro(t_header *header)
{
	ft_printf("Dumping annotated program on standard output\n");
	ft_printf("Program size : %d bytes\n", header->prog_size);
	ft_printf("Name : \"%s\"\n", header->prog_name);
	ft_printf("Comment : \"%s\"\n", header->comment);
}

static void		print_each_octet(t_cmd *cmd)
{
	int			i;
	int			j;

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 4)
		{
			if (cmd->param[i] != NULL && j < cmd->size_param[i])
				ft_printf("%-3d ", cmd->byte_param[i][j]);
			else
				ft_printf("    ");
			j++;
		}
		i++;
	}
	ft_printf("    ");
}

static void		print_sum(t_cmd *cmd)
{
	int			i;

	i = 0;
	while (i < 3)
	{
		if (cmd->param[i])
		{
			if (cmd->value_param[i])
				ft_printf("%-18d", cmd->value_param[i]);
		}
		else
			ft_printf("\t");
		i++;
	}
}

static void		print_cmd(t_cmd *cmd)
{
	int			i;

	i = 0;
	ft_printf("%-5d(%-3d) :\t\t%-10s", cmd->add, cmd->size,
	g_op_tab[cmd->opcode - 1].name);
	while (i < 3)
	{
		if (cmd->param[i])
			ft_printf("%-18s", cmd->param[i]);
		i++;
	}
	ft_printf("\n\t\t\t%-4d", cmd->opcode);
	if (cmd->bytecode != 0)
		ft_printf("%-6d", cmd->bytecode);
	else
		ft_printf("\t  ");
	print_each_octet(cmd);
	ft_printf("\n\t\t\t%-4d", cmd->opcode);
	if (cmd->bytecode != 0)
		ft_printf("%-6d", cmd->bytecode);
	else
		ft_printf("\t  ");
	print_sum(cmd);
	ft_printf("\n\n");
}

void			write_output(t_cmd *cmd, t_label *label, t_header *header)
{
	print_intro(header);
	while (cmd)
	{
		if (label != NULL && label->add == cmd->add)
		{
			ft_printf("%-11d:\t%s:\n", label->add, label->name);
			if (label->next != NULL)
				label = label->next;
		}
		print_cmd(cmd);
		cmd = cmd->next;
	}
}
