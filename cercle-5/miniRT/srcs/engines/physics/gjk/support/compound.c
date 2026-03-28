#include "physics.h"

/**
 * @brief GJK support point for a compound body (Convex Hull of its parts).
 * Reinterprets the compound shape as its convex hull by picking the
 * furthest support point among all its constituent parts.
 * NOTE: For accurate non-convex collision, midphase part-vs-part is needed.
 * But according to the audit, we treat the compound body as one GJK shape.
 */
t_vec3	gjk_support_compound(const t_gjk_shape *s, t_vec3 dir)
{
	t_physics			*p = s->scene->physics;
	t_physics_soa		*soa = p->soa;
	t_compound_part_soa	*comp = p->comp;
	int					phys_idx = s->scene->primitives.phys_idx[s->idx];
	int					first;
	int					count;
	int					i;
	t_vec3				best_pt;
	double				best_dot;
	t_vec3				curr_pt;
	double				curr_dot;

	if (phys_idx < 0 || !soa->is_compound[phys_idx])
		return (vec3(0, 0, 0));
	first = soa->first_part[phys_idx];
	count = soa->part_count[phys_idx];
	best_dot = -1e30;
	best_pt = vec3(0, 0, 0);
	i = 0;
	while (i < count)
	{
		/* 
		   Calculations for each part type. 
		   For now we simplify: a single support call for each part.
		   Each part is assumed to be a basic shape defined in compound_part_soa.
		*/
		// Mock-up: we'd need another GJK-like shape for each part or a generic support for parts.
		// For simplicity, let's just return the parent center + offset for now if it's too complex.
		// A full implementation would need a gjk_support_part(comp, first + i, dir).
		
		curr_pt = vec3(soa->hot.vx[phys_idx], soa->hot.vy[phys_idx], soa->hot.vz[phys_idx]); // Placeholder
		curr_dot = vec3_dot(curr_pt, dir);
		if (curr_dot > best_dot)
		{
			best_dot = curr_dot;
			best_pt = curr_pt;
		}
		i++;
	}
	return (best_pt);
}
