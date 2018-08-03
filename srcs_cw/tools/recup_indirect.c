#include "../../includes/corewar.h"

unsigned int		recup_indirect2(t_mem *mem, t_champ *champ, int start)
{
	int		add;

	add = recup_direct2(mem, champ, start);
	if (add & 0x8000)
		add = add | 0xffff0000;
	return (recup_direct2(mem, champ, add));
}

unsigned int		recup_indirect4(t_mem *mem, t_champ *champ, int start)
{
	int		add;

	add = recup_direct2(mem, champ, start);
	if (add & 0x8000)
		add = add | 0xffff0000;
	return (recup_direct4(mem, champ, add));
}

unsigned int		recup_indirect2x(t_mem *mem, t_champ *champ, int start)
{
	int		add;

	add = recup_direct2(mem, champ, start);
	if (add & 0x8000)
		add = add | 0xffff0000;
	add = add % IDX_MOD;
	return (recup_direct2(mem, champ, add));
}

unsigned int		recup_indirect4x(t_mem *mem, t_champ *champ, int start)
{
	int		add;

	add = recup_direct2(mem, champ, start);
	if (add & 0x8000)
		add = add | 0xffff0000;
	add = add % IDX_MOD;
	return (recup_direct4(mem, champ, add));
}
