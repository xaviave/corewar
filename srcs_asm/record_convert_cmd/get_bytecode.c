/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_bytecode.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xmoreau <xmoreau@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/04 15:01:11 by xmoreau      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/08 12:08:43 by xmoreau     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/asm.h"

static char				get_param_code(char *s, int param)
{
	unsigned char		pcode;

	pcode = 3;
	if (s[0] == 'r')
		pcode = 1;
	if (s[0] == '%')
		pcode = 2;
	pcode = pcode << param;
	return (pcode);
}

char					get_bytecode(char **tab, int j, t_cmd *new)
{
	unsigned char		bytecode;
	unsigned char		p;
	unsigned char		pp;
	unsigned char		ppp;

	p = 0;
	pp = 0;
	ppp = 0;
	if (new->param[0])
		p = get_param_code(tab[j + 1], 6);
	if (new->param[1])
		pp = get_param_code(tab[j + 2], 4);
	if (new->param[2])
		ppp = get_param_code(tab[j + 3], 2);
	bytecode = ((p | pp) | ppp);
	return (bytecode);
}
