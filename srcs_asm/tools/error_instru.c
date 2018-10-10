/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   error_instru.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xmoreau <xmoreau@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/07 14:06:16 by xmoreau      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/04 15:56:53 by xmoreau     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/asm.h"

static void	print_instru(char **tab)
{
	int		i;

	i = 0;
	ft_printf("[ ");
	while (tab[i] != '\0')
	{
		ft_printf("%s ", tab[i]);
		i++;
	}
	ft_printf("] ");
}

static void	arg_error2(char **instru)
{
	ft_printf("A register on line ");
	print_instru(instru);
	ft_printf("is not correct\n");
}

static void	arg_error(int err, char **instru)
{
	if (err == 100)
	{
		ft_printf("The number of parameter on line ");
		print_instru(instru);
		ft_printf("is not correct\n");
		return ;
	}
	if (err < 220)
	{
		ft_printf("The parameter number %d on line ", err % 210);
		print_instru(instru);
		ft_printf("is not correct\n");
		return ;
	}
	if (err % 2)
		arg_error2(instru);
	else
	{
		ft_printf("A label on line ");
		print_instru(instru);
		ft_printf("doesn't exist\n");
	}
}

void		error_instru(t_cmd **cmd, int err, t_stock *stock, char **instru)
{
	if (err == 1000)
		ft_printf("The computer had a problem with memory allocation\n");
	if (err == 2000)
	{
		ft_printf("The instruction on line ");
		print_instru(instru);
		ft_printf("doesn't exist\n");
	}
	if (err > 3000)
		arg_error(err % 3000, instru);
	free_all(*stock->label, stock->inf, cmd);
	exit(EXIT_FAILURE);
}
