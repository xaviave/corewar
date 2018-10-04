/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_bytecode.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xmoreau <xmoreau@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/04 15:01:11 by xmoreau      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/04 15:56:51 by xmoreau     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/asm.h"

static char		get_param_code(char *s, int param)
{
	char		pcode;

	pcode = 3;
	if (ft_strchr(s, 'r') != NULL)
		pcode = 1;
	if (ft_strchr(s, DIRECT_CHAR) != NULL)
		pcode = 2;
	pcode = pcode << param;
	return (pcode);
}

char			get_bytecode(char **tab, int j, t_cmd *new)
{
	char		bytecode;
	char		p;
	char		pp;
	char		ppp;

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
