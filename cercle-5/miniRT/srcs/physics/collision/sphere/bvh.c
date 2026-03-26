/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 09:35:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 13:33:10 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"
#include "scene.h"

static int	check_leaf_ref(t_scene *s, t_sphere *sp, int idx, t_bvh_ref ref,
		t_contact *c)
{
	t_sphere	*o;
	t_vec3		d;
	double		rs;
	double		dist;
	t_mesh		*m;

	if (ref.type == TYPE_SPHERE && ref.index > idx)
	{
		o = &s->spheres[ref.index];
		d = vec3_sub(sp->phys.center, o->phys.center);
		rs = sqrt(sp->radius_sq) + sqrt(o->radius_sq);
		if (vec3_mag_sq(d) >= rs * rs)
			return (0);
		dist = vec3_mag(d);
		c->penetration = rs - dist;
		c->normal = (dist > 1e-12) ? vec3_scale(d, -1.0 / dist) : vec3(0, 1, 0);
		c->contact_point = vec3_add(sp->phys.center, vec3_scale(c->normal,
					sqrt(sp->radius_sq) - c->penetration * 0.5));
		c->a = &sp->phys;
		c->b = &o->phys;
		c->ta = &sp->transform;
		c->tb = &o->transform;
		c->ra = vec3_sub(c->contact_point, sp->phys.center);
		c->rb = vec3_sub(c->contact_point, o->phys.center);
		c->restitution = fmin(sp->phys.elasticity, o->phys.elasticity);
		c->friction = sqrt(sp->phys.friction * o->phys.friction);
		return (1);
	}
	if (ref.type == TYPE_MESH)
	{
		m = &s->meshes[ref.index];
		if (!detect_sphere_mesh_collision(sp, m, &c->normal, &c->penetration))
			return (0);
		c->a = &sp->phys;
		c->ta = &sp->transform;
		c->b = &m->phys;
		c->tb = &m->transform;
		c->restitution = (sp->phys.elasticity + m->phys.elasticity) * 0.5;
		c->friction = (sp->phys.friction + m->phys.friction) * 0.5;
		c->contact_point = vec3_add(sp->phys.center, vec3_scale(c->normal,
					sqrt(sp->radius_sq) - c->penetration));
		c->ra = vec3_sub(c->contact_point, sp->phys.center);
		c->rb = vec3_sub(c->contact_point, m->phys.center);
		return (1);
	}
	return (0);
}

int	traverse_bvh_contacts(t_scene *s, int idx, t_sphere *sp, t_aabb saabb,
		t_contact *c, int count, int max)
{
	int	stack[128];
	int	ptr;
	int	i;
	const t_bvh_node	*node;
	int					k;
	int					end;

	ptr = 0;
	if (!s->bvh || s->bvh->num_nodes == 0)
		return (count);
	stack[ptr++] = 0;
	while (ptr > 0 && count < max)
	{
		i = stack[--ptr];
		node = &s->bvh->nodes[i];
		if (!aabb_overlap(node->bbox, saabb))
			continue ;
		if (node->count > 0)
		{
			k = node->left_or_first;
			end = k + node->count;
			while (k < end && count < max)
				if (check_leaf_ref(s, sp, idx, s->bvh->refs[k++], &c[count]))
					count++;
		}
		else if (ptr < 126)
		{
			stack[ptr++] = node->left_or_first;
			stack[ptr++] = i + 1;
		}
	}
	return (count);
}
