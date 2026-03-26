/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 10:15:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 10:15:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* *****************:********************************************************* */

#include "physics.h"
#include "scene.h"
#include "objects.h"

static int	sphere_vs_capsule(t_sphere *sp, t_capsule *cap, t_contact *c)
{
	t_vec3	p[2]; t_vec3 seg; t_vec3 to_sp; t_vec3 cl; double t;
	p[0] = vec3_sub(cap->transform.pos, vec3_scale(cap->axis, cap->half_height));
	p[1] = vec3_add(cap->transform.pos, vec3_scale(cap->axis, cap->half_height));
	seg = vec3_sub(p[1], p[0]);
	to_sp = vec3_sub(sp->phys.center, p[0]);
	if (vec3_mag_sq(seg) < 1e-12) cl = p[0];
	else
	{
		t = clamp_d(vec3_dot(to_sp, seg) / vec3_mag_sq(seg), 0.0, 1.0);
		cl = vec3_add(p[0], vec3_scale(seg, t));
	}
	if (vec3_mag_sq(vec3_sub(sp->phys.center, cl)) >= pow(sqrt(sp->radius_sq) + cap->radius, 2)) return (0);
	double dist = vec3_mag(vec3_sub(sp->phys.center, cl));
	c->normal = (dist > 1e-9) ? vec3_scale(vec3_sub(sp->phys.center, cl), -1.0 / dist) : vec3(0, -1, 0);
	c->penetration = sqrt(sp->radius_sq) + cap->radius - dist;
	c->a = &sp->phys; c->b = &cap->phys; c->ta = &sp->transform; c->tb = &cap->transform;
	c->contact_point = vec3_add(sp->phys.center, vec3_scale(c->normal, sqrt(sp->radius_sq) - c->penetration * 0.5));
	c->ra = vec3_sub(c->contact_point, sp->phys.center); c->rb = vec3_sub(cl, cap->phys.center);
	c->restitution = fmin(sp->phys.elasticity, cap->phys.elasticity); c->friction = sqrt(sp->phys.friction * cap->phys.friction);
	return (1);
}

int	sphere_others_contacts(t_scene *s, int idx, t_sphere *sp, t_aabb sa, t_gjk_shape *sa_gjk, t_contact *c, int count, int max)
{
	t_gjk_shape sb; int i = -1;
	while (++i < s->box_count && count < max)
		if (aabb_overlap(sa, box_aabb(&s->boxes[i])))
		{
			sb = (t_gjk_shape){&s->boxes[i], gjk_support_box, s->boxes[i].phys.center};
			count += gjk_make_contact(sa_gjk, &sb, &sp->phys, &s->boxes[i].phys, &sp->transform, &s->boxes[i].transform, &c[count]);
		}
	i = -1;
	while (++i < s->capsule_count && count < max) if (aabb_overlap(sa, capsule_aabb(&s->capsules[i]))) count += sphere_vs_capsule(sp, &s->capsules[i], &c[count]);
	i = -1;
	while (++i < s->cylinder_count && count < max) if (aabb_overlap(sa, cylinder_aabb(&s->cylinders[i])))
	{
		sb = (t_gjk_shape){&s->cylinders[i], gjk_support_cylinder, s->cylinders[i].phys.center};
		count += gjk_make_contact(sa_gjk, &sb, &sp->phys, &s->cylinders[i].phys, &sp->transform, &s->cylinders[i].transform, &c[count]);
	}
	i = -1;
	while (++i < s->rect_count && count < max) if (aabb_overlap(sa, rect_aabb(&s->rects[i]))) {
		sb = (t_gjk_shape){&s->rects[i], gjk_support_rect, s->rects[i].phys.center};
		count += gjk_make_contact(sa_gjk, &sb, &sp->phys, &s->rects[i].phys, &sp->transform, &s->rects[i].transform, &c[count]);
	}
	i = -1;
	while (++i < s->tri_count && count < max) if (aabb_overlap(sa, tri_shape_aabb(&s->tris[i]))) {
		sb = (t_gjk_shape){&s->tris[i], gjk_support_tri, s->tris[i].phys.center};
		count += gjk_make_contact(sa_gjk, &sb, &sp->phys, &s->tris[i].phys, &sp->transform, &s->tris[i].xform, &c[count]);
	}
	i = -1;
	while (++i < s->pyramid_count && count < max) if (aabb_overlap(sa, pyramid_aabb(&s->pyramids[i]))) {
		sb = (t_gjk_shape){&s->pyramids[i], gjk_support_pyramid, s->pyramids[i].phys.center};
		count += gjk_make_contact(sa_gjk, &sb, &sp->phys, &s->pyramids[i].phys, &sp->transform, &s->pyramids[i].transform, &c[count]);
	}
	return (count);
}
