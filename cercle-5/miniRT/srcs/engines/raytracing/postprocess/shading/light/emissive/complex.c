/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 10:53:44 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

static void	emissive_box(t_shading *sha, const t_rt_engine *rt, t_vec3 *tot,
		t_emissive_ref r)
{
	double				rad;
	t_primitive_array	*p;

	p = &rt->scene->primitives;
	rad = fmax(fmax(p->ex[r.index], p->ey[r.index]), p->ez[r.index]);
	sha->aux_v = vec3_sub(vec3(p->px[r.index], p->py[r.index], p->pz[r.index]),
			sha->hit->point);
	apply_emissive_hit(sha, tot, &rt->scene->materials[p->mat_ids[r.index]],
		vec3(rad, 0, 0));
}

static void	emissive_capsule(t_shading *sha, const t_rt_engine *rt, t_vec3 *tot,
		t_emissive_ref r)
{
	t_primitive_array	*p;

	p = &rt->scene->primitives;
	sha->aux_v = vec3_sub(vec3(p->px[r.index], p->py[r.index], p->pz[r.index]),
			sha->hit->point);
	apply_emissive_hit(sha, tot, &rt->scene->materials[p->mat_ids[r.index]],
		vec3(p->radii[r.index] + p->heights[r.index] * 0.5, 0, 0));
}

static void	emissive_mesh(t_shading *sha, const t_rt_engine *rt, t_vec3 *tot,
		t_emissive_ref r)
{
	t_vec3			c;
	t_skinned_mesh	*m;
	t_vec3			min;
	t_vec3			max;

	m = &rt->scene->animated[r.index];
	min = vec3(m->bbox.min[0], m->bbox.min[1], m->bbox.min[2]);
	max = vec3(m->bbox.max[0], m->bbox.max[1], m->bbox.max[2]);
	c = vec3_add(min, vec3_scale(vec3_sub(max, min), 0.5));
	sha->aux_v = vec3_sub(c, sha->hit->point);
	apply_emissive_hit(sha, tot, &rt->scene->materials[m->mat_id],
		vec3(vec3_mag(vec3_scale(vec3_sub(max, min), 0.5)), 0, 0));
}

void	emissive_complex(t_shading *sha, const struct s_rt_engine *rt, t_vec3 *tot,
		t_emissive_ref r)
{
	if (r.type == TYPE_BOX)
		emissive_box(sha, rt, tot, r);
	else if (r.type == TYPE_CAPSULE)
		emissive_capsule(sha, rt, tot, r);
	else if (r.type == TYPE_MESH || r.type == TYPE_ANIM)
		emissive_mesh(sha, rt, tot, r);
}
