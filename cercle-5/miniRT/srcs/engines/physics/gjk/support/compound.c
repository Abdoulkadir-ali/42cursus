#include "physics.h"

t_vec3	gjk_support_compound(const t_gjk_shape *s, t_vec3 dir)
{
	int		phys_idx;
	(void)dir;	phys_idx = s->scene->primitives.phys_idx[s->idx];
	if (phys_idx < 0 || !s->phys->soa->is_compound[phys_idx])
		return (vec3(0, 0, 0));
	return (vec3(s->phys->soa->hot.vx[phys_idx],
			s->phys->soa->hot.vy[phys_idx],
			s->phys->soa->hot.vz[phys_idx]));
}
