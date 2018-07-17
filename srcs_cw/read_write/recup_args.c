/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   recup_args.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tduverge <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/12 18:24:29 by tduverge     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/17 13:29:20 by tduverge    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/corewar.h"

unsigned char		recup_octet(t_mem *mem, t_champ *champ, unsigned int n)
{
	return (mem->memory[(champ->pc + n) % MEM_SIZE]);
}

unsigned int		recup_direct2(t_mem *mem, t_champ *champ, unsigned int start)
{
	unsigned int	ret;

	ret = 0;
	ret += recup_octet(mem, champ, start) << 8;
	ret += recup_octet(mem, champ, start + 1);
	return (ret);
}

unsigned int		recup_direct4(t_mem *mem, t_champ *champ, unsigned int start)
{
	unsigned int	ret;

	ret = 0;
	ret += recup_octet(mem, champ, start) << 24;
	ret += recup_octet(mem, champ, start + 1) << 16;
	ret += recup_octet(mem, champ, start + 2) << 8;
	ret += recup_octet(mem, champ, start + 3);
	return (ret);
}

unsigned int		recup_indirect2(t_mem *mem, t_champ *champ, unsigned int start)
{
	unsigned int	add;

	add = recup_direct2(mem, champ, start);
	return (recup_direct2(mem, champ, add));
}

unsigned int		recup_indirect4(t_mem *mem, t_champ *champ, unsigned int start)
{
	int		add;

	add = recup_direct2(mem, champ, start);
	return (recup_direct4(mem, champ, add));
}

unsigned int		recup_indirect2x(t_mem *mem, t_champ *champ, unsigned int start)
{
	unsigned int	add;

	add = recup_direct2(mem, champ, start);
	if (add & 0x8000)
		add = add % IDX_MOD - 512;
	else
		add = add % IDX_MOD;
	return (recup_direct2(mem, champ, add));
}

unsigned int		recup_indirect4x(t_mem *mem, t_champ *champ, unsigned int start)
{
	unsigned int	add;

	add = recup_direct2(mem, champ, start);
	if (add & 0x8000)
		add = add % IDX_MOD - 512;
	else
		add = add % IDX_MOD;
	return (recup_direct4(mem, champ, add));
}
