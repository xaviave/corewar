/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main_asm.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xmoreau <xmoreau@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/19 13:49:01 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/20 18:10:48 by xmoreau     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/asm.h"

int 	main(int ac, char **av)
{
	if (ac < 2)
		ft_printf("Usage: ./src_asm [-a] <sourcefile.s>\n\t-a : 
		Instead of creating a .cor file, outputs a stripped and 
		annotated version of the code to the standard output");
	else
		red_code(av);
	return (0);
}
/*
si le fichier n'exite pas : Can't read source file "file_name"
si pas de ".s" le fichier .cor n'a pas de nom et s'appelle ".cor"
*/