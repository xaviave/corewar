/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   recup_direct.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tduverge <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/22 14:24:42 by tduverge     #+#   ##    ##    #+#       */
/*   Updated: 2018/08/22 14:24:43 by tduverge    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/corewar.h"

unsigned char		recup_octet(t_mem *mem, t_champ *champ, int n)
{
	return (mem->memory[((champ->pc + n) % MEM_SIZE + MEM_SIZE) % MEM_SIZE]);
}

unsigned int		recup_direct2(t_mem *mem, t_champ *champ, int start)
{
	unsigned int	ret;

	ret = 0;
	ret += recup_octet(mem, champ, start) << 8;
	ret += recup_octet(mem, champ, start + 1);
	return (ret);
}

unsigned int		recup_direct4(t_mem *mem, t_champ *champ, int start)
{
	unsigned int	ret;

	ret = 0;
	ret += recup_octet(mem, champ, start) << 24;
	ret += recup_octet(mem, champ, start + 1) << 16;
	ret += recup_octet(mem, champ, start + 2) << 8;
	ret += recup_octet(mem, champ, start + 3);
	return (ret);
}
