/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main_asm.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tduverge <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/25 12:04:14 by tduverge     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/03 16:54:35 by xamartin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/asm.h"

int		main(int argc, char **argv)
{
	char	*file;
	t_all	a;

	file = ft_first(argc, argv);
	ft_parsing(&file, &a);
	/* si le fichier est valide */
	ft_third(/* parametres apres parsing */argv, argc, &a);
	return (0);
}
