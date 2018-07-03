/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   asm.h                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xmoreau <xmoreau@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/20 17:53:02 by xmoreau      #+#   ##    ##    #+#       */
/*   Updated: 2018/06/28 13:18:49 by lotoussa    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "../libft/header/libft.h"

# define _USAGE "[-a] <sourcefile.s>\n    -a : Instead of creating a .cor \
file, outputs a stripped and annotated version of the code to the standard \
output\n"

int				ft_first(int argc, char **argv, char **file);

#endif
