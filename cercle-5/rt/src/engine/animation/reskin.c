/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reskin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 03:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/30 00:32:04 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "skeletal.h"

/* Apply the load-time outer transform (pre 3x3, scale, origin, optional 4x4)
 * to a vertex already expressed in animator-local space. */
static t_vec3	apply_outer(const t_animator *a, t_vec3 p)
{
	t_vec3	o;

	o.x = v3_dot(v3(a->pre[0], a->pre[1], a->pre[2]), p);
	o.y = v3_dot(v3(a->pre[3], a->pre[4], a->pre[5]), p);
	o.z = v3_dot(v3(a->pre[6], a->pre[7], a->pre[8]), p);
	o = v3_add(v3_mul(o, a->pre_scale), a->pre_origin);
	if (a->has_extra)
		o = skel_m4_xform_pos(a->extra, o);
	return (o);
}

/* Skinning result is already in scene-space (animator-local).
 * Layer the load-time outer transform on top. */
static t_vec3	finalize_vertex(const t_reskin *c, int v)
{
	return (apply_outer(c->a, skel_skin_vertex(c->a, c->p, v)));
}

static void	write_triangle(const t_reskin *c, int ti)
{
	const unsigned int	*idx = &c->p->indices[ti * 3];
	t_object			*o;

	if ((int)idx[0] >= c->p->n_verts || (int)idx[1] >= c->p->n_verts
		|| (int)idx[2] >= c->p->n_verts)
		return ;
	if (c->p->bvh_base + ti < 0 || c->p->bvh_base + ti >= (int)c->s->n_bvh
		|| c->s->bvh_objs[c->p->bvh_base + ti].type != OBJ_TRIANGLE)
		return ;
	o = &c->s->bvh_objs[c->p->bvh_base + ti];
	o->u.tri.a = finalize_vertex(c, idx[0]);
	o->u.tri.b = finalize_vertex(c, idx[1]);
	o->u.tri.c = finalize_vertex(c, idx[2]);
	o->u.tri.n = v3_norm(v3_cross(v3_sub(o->u.tri.b, o->u.tri.a),
				v3_sub(o->u.tri.c, o->u.tri.a)));
}

static void	reskin_prim(t_animator *a, t_anim_prim *p, t_scene *s)
{
	t_reskin	c;
	int			ti;

	c.a = a;
	c.p = p;
	c.s = s;
	c.has_inv = 0;
	if (p->skin >= 0)
		skel_build_palette(a, p->skin);
	ti = -1;
	while (++ti < p->n_tris)
		write_triangle(&c, ti);
}

void	skel_reskin_all(t_animator *a, t_scene *s)
{
	int	i;

	i = -1;
	while (++i < a->n_prims)
		reskin_prim(a, &a->prims[i], s);
}
