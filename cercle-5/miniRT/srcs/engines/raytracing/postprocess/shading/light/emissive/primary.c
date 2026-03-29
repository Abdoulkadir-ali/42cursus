/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primary.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 10:53:45 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

static void	emissive_sphere(t_shading *sha, const t_rt_engine *rt, t_vec3 *tot,
		t_emissive_ref r)
{
	double				rad;
	t_primitive_array	*p;

	p = &rt->scene->primitives;
	rad = fmax(fabs(p->ex[r.index]), 1.0) * p->radii[r.index];
	sha->aux_v = vec3_sub(vec3(p->px[r.index], p->py[r.index], p->pz[r.index]),
			sha->hit->point);
	apply_emissive_hit(sha, tot, &rt->scene->materials[p->mat_ids[r.index]],
		vec3(rad, 0, 0));
}

static void	emissive_tri(t_shading *sha, const t_rt_engine *rt, t_vec3 *tot,
		t_emissive_ref r)
{
	t_vec3		c;
	t_tri_array	*t;

	t = &rt->scene->tri_soa;
	c = vec3_scale(vec3_add(vec3_add(
					vec3(t->vx[0][r.index], t->vy[0][r.index], t->vz[0][r.index]),
					vec3(t->vx[1][r.index], t->vy[1][r.index], t->vz[1][r.index])),
				vec3(t->vx[2][r.index], t->vy[2][r.index], t->vz[2][r.index])),
			1.0 / 3.0);
	sha->aux_v = vec3_sub(c, sha->hit->point);
	apply_emissive_hit(sha, tot, &rt->scene->materials[t->mat_ids[r.index]],
		vec3(0.5, 0, 0));
}

static void	emissive_rect(t_shading *sha, const t_rt_engine *rt, t_vec3 *tot,
		t_emissive_ref r)
{
	t_primitive_array	*p;

	p = &rt->scene->primitives;
	sha->aux_v = vec3_sub(vec3(p->px[r.index], p->py[r.index], p->pz[r.index]),
			sha->hit->point);
	apply_emissive_hit(sha, tot, &rt->scene->materials[p->mat_ids[r.index]],
		vec3(0.7, 0, 0));
}

static void	emissive_pyramid(t_shading *sha, const t_rt_engine *rt, t_vec3 *tot,
		t_emissive_ref r)
{
	t_primitive_array	*p;

	p = &rt->scene->primitives;
	sha->aux_v = vec3_sub(vec3(p->px[r.index], p->py[r.index], p->pz[r.index]),
			sha->hit->point);
	apply_emissive_hit(sha, tot, &rt->scene->materials[p->mat_ids[r.index]],
		vec3(p->ex[r.index] * 0.5, 0, 0));
}

void	emissive_primary(t_shading *sha, const t_rt_engine *rt, t_vec3 *tot,
		t_emissive_ref r)
{
	DBG_TRACE_MSG(DBG_CH_RENDER,
		"emissive_primary: type=%d idx=%d\n", r.type, r.index);
	if (r.type == TYPE_SPHERE)
		emissive_sphere(sha, rt, tot, r);
	else if (r.type == TYPE_TRI)
		emissive_tri(sha, rt, tot, r);
	else if (r.type == TYPE_RECT)
		emissive_rect(sha, rt, tot, r);
	else if (r.type == TYPE_PYRAMID)
		emissive_pyramid(sha, rt, tot, r);
	else
		DBG_WARN_MSG(DBG_CH_RENDER,
			"emissive_primary: unknown type=%d\n", r.type);
}
