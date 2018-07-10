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
	char	**split;

	file = ft_first(argc, argv);
	split = ft_parsing(file);
	free(file);
	/* si le fichier est valide */
	ft_third(/* parametres apres parsing */argv, argc);
	return (0);
}
