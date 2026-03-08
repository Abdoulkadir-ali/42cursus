/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collide.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 20:31:31 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/06 20:31:31 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "physics.h"
#include "scene.h"

bool	collide_sphere_sphere(t_sphere *a, t_sphere *b, t_contact *c)
{
	t_vec3	delta;
	double	dist_sq;
	double	r_sum;
	double	dist;

	delta = vec3_sub(b->transform.pos, a->transform.pos);
	dist_sq = vec3_mag_sq(delta);
	r_sum = sqrt(a->radius_sq) + sqrt(b->radius_sq);
	if (dist_sq > r_sum * r_sum || dist_sq < 1e-8)
		return (false);
	dist = sqrt(dist_sq);
	c->normal = vec3_scale(delta, 1.0 / dist);
	c->penetration = r_sum - dist;
	c->a = &a->phys;
	c->b = &b->phys;
	c->ta = &a->transform;
	c->tb = &b->transform;
	c->contact_point = vec3_add(a->transform.pos,
			vec3_scale(c->normal, sqrt(a->radius_sq)));
	c->ra = vec3_sub(c->contact_point, a->transform.pos);
	c->rb = vec3_sub(c->contact_point, b->transform.pos);
	c->restitution = fmin(a->phys.elasticity, b->phys.elasticity);
	c->friction = sqrt(a->phys.friction * b->phys.friction);
	return (true);
}

bool	collide_sphere_plane(t_sphere *s, t_plane *pl, t_contact *c)
{
	t_vec3	normal;
	t_vec3	to_center;
	double	dist;
	double	radius;

	normal = pl->transform.up;
	if (vec3_mag_sq(normal) < 1e-6)
		normal = (t_vec3){0, 1, 0, 0};
	else
		normal = vec3_norm(normal);
	to_center = vec3_sub(s->transform.pos, pl->transform.pos);
	dist = vec3_dot(to_center, normal);
	radius = sqrt(s->radius_sq);
	if (dist >= radius)
		return (false);
	c->normal = vec3_scale(normal, -1.0);
	c->penetration = radius - dist;
	c->a = &s->phys;
	c->b = NULL;
	c->ta = &s->transform;
	c->tb = &pl->transform;
	c->contact_point = vec3_sub(s->transform.pos,
			vec3_scale(normal, radius));
	c->ra = vec3_sub(c->contact_point, s->transform.pos);
	c->rb = vec3(0, 0, 0);
	c->restitution = fmin(s->phys.elasticity, 0.5);
	c->friction = sqrt(s->phys.friction * 0.5);
	return (true);
}

bool	collide_sphere_mesh(t_sphere *s, t_mesh *m, t_contact *c)
{
	t_vec3	n;
	double	pen;

	if (!detect_sphere_mesh_collision(s, m, &n, &pen))
		return (false);
	c->normal = n;
	c->penetration = pen;
	c->a = &s->phys;
	c->b = NULL;
	c->ta = &s->transform;
	c->tb = &m->transform;
	c->contact_point = vec3_sub(s->transform.pos,
			vec3_scale(n, sqrt(s->radius_sq)));
	c->ra = vec3_sub(c->contact_point, s->transform.pos);
	c->rb = vec3(0, 0, 0);
	c->restitution = s->phys.elasticity;
	c->friction = sqrt(s->phys.friction * m->phys.friction);
	return (true);
}

static t_vec3	safe_plane_normal(t_plane *pl)
{
	if (vec3_mag_sq(pl->transform.up) < 1e-6)
		return (vec3(0, 1, 0));
	return (vec3_norm(pl->transform.up));
}

static bool	vertex_vs_plane(t_vec3 v, t_plane *pl, t_vec3 n,
		t_physics_body *pb, t_transform *tr, double elasticity,
		t_contact *c)
{
	t_vec3	to_v;
	double	dist;

	to_v = vec3_sub(v, pl->transform.pos);
	dist = vec3_dot(to_v, n);
	if (dist >= 0.0)
		return (false);
	c->normal = vec3_scale(n, -1.0);
	c->penetration = -dist;
	c->a = pb;
	c->b = NULL;
	c->ta = tr;
	c->tb = &pl->transform;
	c->contact_point = v;
	c->ra = vec3_sub(v, tr->pos);
	c->rb = vec3(0, 0, 0);
	c->restitution = fmin(elasticity, 0.5);
	c->friction = sqrt(pb->friction * 0.5);
	return (true);
}

int	collide_tri_plane(t_tri_shape *tr, t_plane *pl, t_contact *c, int max_c)
{
	t_vec3		n;
	t_contact	tmp;
	int			count;
	int			i;

	n = safe_plane_normal(pl);
	count = 0;
	i = 0;
	while (i < 3 && count < max_c)
	{
		if (vertex_vs_plane(tr->v[i], pl, n, &tr->phys, &tr->xform,
				tr->phys.elasticity, &tmp))
			c[count++] = tmp;
		i++;
	}
	return (count);
}

int	collide_rect_plane(t_rect *rc, t_plane *pl, t_contact *c, int max_c)
{
	t_vec3		n;
	t_contact	tmp;
	int			count;
	int			i;

	n = safe_plane_normal(pl);
	count = 0;
	i = 0;
	while (i < 4 && count < max_c)
	{
		if (vertex_vs_plane(rc->v[i], pl, n, &rc->phys, &rc->transform,
				rc->phys.elasticity, &tmp))
			c[count++] = tmp;
		i++;
	}
	return (count);
}

static void	pyramid_get_verts(t_pyramid *py, t_vec3 verts[5])
{
	t_vec3	ref;
	t_vec3	right;
	t_vec3	fwd;
	double	h;

	h = py->base_size * 0.5;
	if (fabs(py->up.y) < 0.9)
		ref = vec3(0, 1, 0);
	else
		ref = vec3(1, 0, 0);
	right = vec3_norm(vec3_cross(py->up, ref));
	fwd = vec3_cross(right, py->up);
	verts[0] = vec3_add(vec3_add(py->transform.pos, vec3_scale(right, h)),
			vec3_scale(fwd, h));
	verts[1] = vec3_add(vec3_add(py->transform.pos, vec3_scale(right, -h)),
			vec3_scale(fwd, h));
	verts[2] = vec3_add(vec3_add(py->transform.pos, vec3_scale(right, -h)),
			vec3_scale(fwd, -h));
	verts[3] = vec3_add(vec3_add(py->transform.pos, vec3_scale(right, h)),
			vec3_scale(fwd, -h));
	verts[4] = vec3_add(py->transform.pos, vec3_scale(py->up, py->height));
}

int	collide_pyramid_plane(t_pyramid *py, t_plane *pl, t_contact *c, int max_c)
{
	t_vec3		n;
	t_vec3		verts[5];
	t_contact	tmp;
	int			count;
	int			i;

	n = safe_plane_normal(pl);
	pyramid_get_verts(py, verts);
	count = 0;
	i = 0;
	while (i < 5 && count < max_c)
	{
		if (vertex_vs_plane(verts[i], pl, n, &py->phys, &py->transform,
				py->phys.elasticity, &tmp))
			c[count++] = tmp;
		i++;
	}
	return (count);
}

/* Report ALL penetrating corners (up to 8) - fixes box rocking on plane */
int	collide_box_plane(t_box *bx, t_plane *pl, t_contact *c, int max_c)
{
	t_vec3		n;
	t_vec3		ax[3];
	t_vec3		corner;
	t_contact	best;
	int			count;
	int			i;
	int			sx;
	int			sy;
	int			sz;

	n = safe_plane_normal(pl);
	ax[0] = vec3_norm(bx->transform.forward);
	vec3_orthonormal_basis(ax[0], &ax[1], &ax[2]);
	count = 0;
	i = 0;
	while (i < 8 && count < max_c)
	{
		sx = ((i & 1) != 0) ? 1 : -1;
		sy = ((i & 2) != 0) ? 1 : -1;
		sz = ((i & 4) != 0) ? 1 : -1;
		corner = vec3_add(bx->transform.pos,
				vec3_add(vec3_scale(ax[0], sx * bx->half_extents.x),
				vec3_add(vec3_scale(ax[1], sy * bx->half_extents.y),
				vec3_scale(ax[2], sz * bx->half_extents.z))));
		if (vertex_vs_plane(corner, pl, n, &bx->phys, &bx->transform,
				bx->phys.elasticity, &best))
			c[count++] = best;
		i++;
	}
	return (count);
}

/* Report both endpoint contacts when both endpoints are below plane */
int	collide_capsule_plane(t_capsule *cap, t_plane *pl, t_contact *c, int max_c)
{
	t_vec3		n;
	t_vec3		p0;
	t_vec3		p1;
	t_vec3		sphere_c;
	t_contact	best;
	int			count;
	double		dist;
	double		pen;
	int			s;

	n = safe_plane_normal(pl);
	p0 = vec3_add(cap->transform.pos,
			vec3_scale(cap->axis, cap->half_height));
	p1 = vec3_sub(cap->transform.pos,
			vec3_scale(cap->axis, cap->half_height));
	count = 0;
	s = 0;
	while (s < 2 && count < max_c)
	{
		if (s == 0)
			sphere_c = p0;
		else
			sphere_c = p1;
		dist = vec3_dot(vec3_sub(sphere_c, pl->transform.pos), n);
		pen = cap->radius - dist;
		if (pen > 0.0)
		{
			best.normal = vec3_scale(n, -1.0);
			best.penetration = pen;
			best.a = &cap->phys;
			best.b = NULL;
			best.ta = &cap->transform;
			best.tb = &pl->transform;
			best.contact_point = vec3_add(sphere_c,
					vec3_scale(n, -cap->radius));
			best.ra = vec3_sub(best.contact_point, cap->transform.pos);
			best.rb = vec3(0, 0, 0);
			best.restitution = fmin(cap->phys.elasticity, 0.5);
			best.friction = sqrt(cap->phys.friction * 0.5);
			c[count++] = best;
		}
		s++;
	}
	return (count);
}
int	collide_cylinder_plane(t_cylinder *cy, t_plane *pl, t_contact *c, int max_c)
{
	t_vec3		n;
	t_vec3		ax;
	t_vec3		p0;
	t_vec3		p1;
	t_vec3		sphere_c;
	t_contact	best;
	int			count;
	double		dist;
	double		pen;
	double		radius;
	int			s;

	n = safe_plane_normal(pl);
	ax = vec3_norm(cy->transform.forward);
	radius = cy->transform.scale.x;
	/* transform.pos is the bottom base; p0 = bottom cap, p1 = top cap */
	p0 = cy->transform.pos;
	p1 = vec3_add(cy->transform.pos, vec3_scale(ax, cy->transform.scale.y));
	count = 0;
	s = 0;
	while (s < 2 && count < max_c)
	{
		if (s == 0)
			sphere_c = p0;
		else
			sphere_c = p1;
		dist = vec3_dot(vec3_sub(sphere_c, pl->transform.pos), n);
		pen = radius - dist;
		if (pen > 0.0)
		{
			best.normal = vec3_scale(n, -1.0);
			best.penetration = pen;
			best.a = &cy->phys;
			best.b = NULL;
			best.ta = &cy->transform;
			best.tb = &pl->transform;
			best.contact_point = vec3_add(sphere_c,
					vec3_scale(n, -radius));
			best.ra = vec3_sub(best.contact_point, cy->phys.center);
			best.rb = vec3(0, 0, 0);
			best.restitution = fmin(cy->phys.elasticity, 0.5);
			best.friction = sqrt(cy->phys.friction * 0.5);
			c[count++] = best;
		}
		s++;
	}
	return (count);
}

/* ── closest point on segment (p0,p1) to point pt ─────────────────────── */
static t_vec3	seg_closest(t_vec3 p0, t_vec3 p1, t_vec3 pt)
{
	t_vec3	d;
	double	t;
	double	len2;

	d = vec3_sub(p1, p0);
	len2 = vec3_mag_sq(d);
	if (len2 < 1e-9)
		return (p0);
	t = vec3_dot(vec3_sub(pt, p0), d) / len2;
	if (t < 0.0)
		t = 0.0;
	if (t > 1.0)
		t = 1.0;
	return (vec3_add(p0, vec3_scale(d, t)));
}

bool	collide_sphere_capsule(t_sphere *sp, t_capsule *cap, t_contact *c)
{
	t_vec3	p0;
	t_vec3	p1;
	t_vec3	closest;
	t_vec3	delta;
	double	dist_sq;
	double	dist;
	double	r;
	double	r_sum;

	p0 = vec3_add(cap->transform.pos,
			vec3_scale(cap->axis, cap->half_height));
	p1 = vec3_sub(cap->transform.pos,
			vec3_scale(cap->axis, cap->half_height));
	closest = seg_closest(p0, p1, sp->transform.pos);
	delta = vec3_sub(sp->transform.pos, closest);
	dist_sq = vec3_mag_sq(delta);
	r = sqrt(sp->radius_sq);
	r_sum = r + cap->radius;
	if (dist_sq >= r_sum * r_sum)
		return (false);
	dist = sqrt(dist_sq);
	if (dist < 1e-9)
		c->normal = vec3(0, 1, 0);
	else
		c->normal = vec3_scale(delta, 1.0 / dist);
	c->penetration = r_sum - dist;
	c->a = &sp->phys;
	c->b = &cap->phys;
	c->ta = &sp->transform;
	c->tb = &cap->transform;
	c->contact_point = closest;
	c->ra = vec3_sub(closest, sp->transform.pos);
	c->rb = vec3_sub(closest, cap->transform.pos);
	c->restitution = fmin(sp->phys.elasticity, cap->phys.elasticity);
	c->friction = sqrt(sp->phys.friction * cap->phys.friction);
	return (true);
}

bool	collide_sphere_box(t_sphere *sp, t_box *bx, t_contact *c)
{
	t_vec3	sp_c;
	t_vec3	ax[3];
	t_vec3	d;
	t_vec3	clamped;
	t_vec3	closest;
	t_vec3	delta;
	double	dist_sq;
	double	dist;
	double	r;

	sp_c = sp->transform.pos;
	r = sqrt(sp->radius_sq);
	ax[0] = vec3_norm(bx->transform.forward);
	vec3_orthonormal_basis(ax[0], &ax[1], &ax[2]);
	d.x = vec3_dot(vec3_sub(sp_c, bx->transform.pos), ax[0]);
	d.y = vec3_dot(vec3_sub(sp_c, bx->transform.pos), ax[1]);
	d.z = vec3_dot(vec3_sub(sp_c, bx->transform.pos), ax[2]);
	clamped.x = clamp_d(d.x, -bx->half_extents.x, bx->half_extents.x);
	clamped.y = clamp_d(d.y, -bx->half_extents.y, bx->half_extents.y);
	clamped.z = clamp_d(d.z, -bx->half_extents.z, bx->half_extents.z);
	closest = vec3_add(bx->transform.pos,
			vec3_add(vec3_scale(ax[0], clamped.x),
			vec3_add(vec3_scale(ax[1], clamped.y),
			vec3_scale(ax[2], clamped.z))));
	delta = vec3_sub(sp_c, closest);
	dist_sq = vec3_mag_sq(delta);
	if (dist_sq >= r * r)
		return (false);
	dist = sqrt(dist_sq);
	if (dist < 1e-9)
		c->normal = vec3(0, 1, 0);
	else
		c->normal = vec3_scale(delta, 1.0 / dist);
	c->penetration = r - dist;
	c->a = &sp->phys;
	c->b = &bx->phys;
	c->ta = &sp->transform;
	c->tb = &bx->transform;
	c->contact_point = closest;
	c->ra = vec3_sub(closest, sp_c);
	c->rb = vec3_sub(closest, bx->transform.pos);
	c->restitution = fmin(sp->phys.elasticity, bx->phys.elasticity);
	c->friction = sqrt(sp->phys.friction * bx->phys.friction);
	return (true);
}

/* ── closest points on two finite segments (Ericson §5.1.9) ─────────────── */
static void	seg_seg_closest(t_vec3 p0, t_vec3 p1, t_vec3 q0, t_vec3 q1,
		t_vec3 *P, t_vec3 *Q)
{
	t_vec3	d1;
	t_vec3	d2;
	t_vec3	r;
	double	a;
	double	e;
	double	f;
	double	b;
	double	co;
	double	denom;
	double	s;
	double	t;

	d1 = vec3_sub(p1, p0);
	d2 = vec3_sub(q1, q0);
	r = vec3_sub(p0, q0);
	a = vec3_mag_sq(d1);
	e = vec3_mag_sq(d2);
	f = vec3_dot(d2, r);
	s = 0.0;
	t = 0.0;
	if (a > 1e-9 && e > 1e-9)
	{
		b = vec3_dot(d1, d2);
		co = vec3_dot(d1, r);
		denom = a * e - b * b;
		if (denom > 1e-9)
			s = clamp_d((b * f - co * e) / denom, 0.0, 1.0);
		t = (b * s + f) / e;
		if (t < 0.0)
		{
			t = 0.0;
			s = clamp_d(-co / a, 0.0, 1.0);
		}
		else if (t > 1.0)
		{
			t = 1.0;
			s = clamp_d((b - co) / a, 0.0, 1.0);
		}
	}
	else if (e > 1e-9)
		t = clamp_d(f / e, 0.0, 1.0);
	*P = vec3_add(p0, vec3_scale(d1, s));
	*Q = vec3_add(q0, vec3_scale(d2, t));
}

bool	collide_capsule_capsule(t_capsule *a, t_capsule *b, t_contact *c)
{
	t_vec3	p0;
	t_vec3	p1;
	t_vec3	q0;
	t_vec3	q1;
	t_vec3	P;
	t_vec3	Q;
	t_vec3	delta;
	double	dist_sq;
	double	dist;
	double	r_sum;

	p0 = vec3_add(a->transform.pos, vec3_scale(a->axis, a->half_height));
	p1 = vec3_sub(a->transform.pos, vec3_scale(a->axis, a->half_height));
	q0 = vec3_add(b->transform.pos, vec3_scale(b->axis, b->half_height));
	q1 = vec3_sub(b->transform.pos, vec3_scale(b->axis, b->half_height));
	seg_seg_closest(p0, p1, q0, q1, &P, &Q);
	delta = vec3_sub(P, Q);
	dist_sq = vec3_mag_sq(delta);
	r_sum = a->radius + b->radius;
	if (dist_sq >= r_sum * r_sum)
		return (false);
	dist = sqrt(dist_sq);
	if (dist < 1e-9)
		c->normal = vec3(0, 1, 0);
	else
		c->normal = vec3_scale(delta, 1.0 / dist);
	c->penetration = r_sum - dist;
	c->a = &a->phys;
	c->b = &b->phys;
	c->ta = &a->transform;
	c->tb = &b->transform;
	c->contact_point = vec3_scale(vec3_add(P, Q), 0.5);
	c->ra = vec3_sub(c->contact_point, a->transform.pos);
	c->rb = vec3_sub(c->contact_point, b->transform.pos);
	c->restitution = fmin(a->phys.elasticity, b->phys.elasticity);
	c->friction = sqrt(a->phys.friction * b->phys.friction);
	return (true);
}

/*
** Support vertex of an OBB in direction dir (corner deepest along dir).
*/
static t_vec3	support_vtx(t_vec3 center, t_vec3 ax[3], t_vec3 he, t_vec3 dir)
{
	t_vec3	p;

	p = center;
	if (vec3_dot(ax[0], dir) < 0.0)
		p = vec3_add(p, vec3_scale(ax[0], he.x));
	else
		p = vec3_sub(p, vec3_scale(ax[0], he.x));
	if (vec3_dot(ax[1], dir) < 0.0)
		p = vec3_add(p, vec3_scale(ax[1], he.y));
	else
		p = vec3_sub(p, vec3_scale(ax[1], he.y));
	if (vec3_dot(ax[2], dir) < 0.0)
		p = vec3_add(p, vec3_scale(ax[2], he.z));
	else
		p = vec3_sub(p, vec3_scale(ax[2], he.z));
	return (p);
}

/*
** Box vs Box — Separating Axis Test on 15 axes (3+3 face normals + 9 edges).
** Returns the contact with minimum penetration depth.
*/
static double	sat_overlap(t_vec3 ax, t_vec3 d,
		t_vec3 a[3], t_vec3 he_a, t_vec3 b[3], t_vec3 he_b)
{
	double	r_a;
	double	r_b;

	r_a = fabs(vec3_dot(a[0], ax)) * he_a.x
		+ fabs(vec3_dot(a[1], ax)) * he_a.y
		+ fabs(vec3_dot(a[2], ax)) * he_a.z;
	r_b = fabs(vec3_dot(b[0], ax)) * he_b.x
		+ fabs(vec3_dot(b[1], ax)) * he_b.y
		+ fabs(vec3_dot(b[2], ax)) * he_b.z;
	return ((r_a + r_b) - fabs(vec3_dot(d, ax)));
}

bool	collide_box_box(t_box *a, t_box *b, t_contact *c)
{
	t_vec3	aa[3];
	t_vec3	ba[3];
	t_vec3	d;
	t_vec3	axes[15];
	int		best;
	double	min_ov;
	double	ov;
	int		i;
	t_vec3	ax;

	aa[0] = vec3_norm(a->transform.forward);
	vec3_orthonormal_basis(aa[0], &aa[1], &aa[2]);
	ba[0] = vec3_norm(b->transform.forward);
	vec3_orthonormal_basis(ba[0], &ba[1], &ba[2]);
	d = vec3_sub(b->transform.pos, a->transform.pos);
	i = 0;
	while (i < 3)
	{
		axes[i] = aa[i];
		axes[3 + i] = ba[i];
		i++;
	}
	i = 0;
	while (i < 3)
	{
		axes[6 + i * 3 + 0] = vec3_cross(aa[i], ba[0]);
		axes[6 + i * 3 + 1] = vec3_cross(aa[i], ba[1]);
		axes[6 + i * 3 + 2] = vec3_cross(aa[i], ba[2]);
		i++;
	}
	min_ov = 1e30;
	best = -1;
	i = 0;
	while (i < 15)
	{
		ax = axes[i];
		if (vec3_mag_sq(ax) < 1e-9)
		{
			i++;
			continue ;
		}
		ax = vec3_norm(ax);
		axes[i] = ax;
		ov = sat_overlap(ax, d, aa, a->half_extents, ba, b->half_extents);
		if (ov < 0.0)
			return (false);
		if (ov < min_ov)
		{
			min_ov = ov;
			best = i;
		}
		i++;
	}
	if (best < 0)
		return (false);
	ax = axes[best];
	if (vec3_dot(ax, d) < 0.0)
		ax = vec3_scale(ax, -1.0);
	c->normal = ax;
	c->penetration = min_ov;
	c->a = &a->phys;
	c->b = &b->phys;
	c->ta = &a->transform;
	c->tb = &b->transform;
	/*
	** Contact point: use support vertex instead of center midpoint.
	** Face-A axis (best 0-2): deepest vertex of B in -normal direction.
	** Face-B axis (best 3-5): deepest vertex of A in +normal direction.
	** Edge-edge  (best 6-14): midpoint of centers (good enough for brief contact).
	*/
	if (best < 3)
		c->contact_point = support_vtx(b->phys.center, ba, b->half_extents,
				vec3_scale(ax, -1.0));
	else if (best < 6)
		c->contact_point = support_vtx(a->phys.center, aa, a->half_extents, ax);
	else
		c->contact_point = vec3_scale(
				vec3_add(a->phys.center, b->phys.center), 0.5);
	c->ra = vec3_sub(c->contact_point, a->phys.center);
	c->rb = vec3_sub(c->contact_point, b->phys.center);
	c->restitution = fmin(a->phys.elasticity, b->phys.elasticity);
	c->friction = sqrt(a->phys.friction * b->phys.friction);
	return (true);
}

/*
** Box vs Capsule — find closest point on capsule segment to box center,
** clamp it into OBB local space, then sphere-vs-point test.
*/
/*
** Sample 5 points along capsule segment; for each find closest on OBB surface;
** keep the sample with minimum distance. This is correct for all configurations
** unlike the old "closest to box center" approach.
*/
bool	collide_box_capsule(t_box *bx, t_capsule *cap, t_contact *c)
{
	t_vec3	ax[3];
	t_vec3	seg_p0;
	t_vec3	seg_p1;
	t_vec3	pt;
	t_vec3	local;
	t_vec3	clamped;
	t_vec3	closest_on_box;
	t_vec3	delta;
	t_vec3	best_pt;
	t_vec3	best_box_pt;
	double	best_dist;
	double	dist_sq;
	double	dist;
	double	t;
	int		i;

	ax[0] = vec3_norm(bx->transform.forward);
	vec3_orthonormal_basis(ax[0], &ax[1], &ax[2]);
	seg_p0 = vec3_add(cap->transform.pos,
			vec3_scale(cap->axis, cap->half_height));
	seg_p1 = vec3_sub(cap->transform.pos,
			vec3_scale(cap->axis, cap->half_height));
	best_dist = 1e30;
	best_pt = seg_p0;
	best_box_pt = bx->phys.center;
	i = 0;
	while (i <= 4)
	{
		t = i * 0.25;
		pt = vec3_add(vec3_scale(seg_p0, 1.0 - t),
				vec3_scale(seg_p1, t));
		local.x = vec3_dot(vec3_sub(pt, bx->phys.center), ax[0]);
		local.y = vec3_dot(vec3_sub(pt, bx->phys.center), ax[1]);
		local.z = vec3_dot(vec3_sub(pt, bx->phys.center), ax[2]);
		clamped.x = fmax(-bx->half_extents.x,
				fmin(bx->half_extents.x, local.x));
		clamped.y = fmax(-bx->half_extents.y,
				fmin(bx->half_extents.y, local.y));
		clamped.z = fmax(-bx->half_extents.z,
				fmin(bx->half_extents.z, local.z));
		closest_on_box = vec3_add(bx->phys.center,
				vec3_add(vec3_scale(ax[0], clamped.x),
				vec3_add(vec3_scale(ax[1], clamped.y),
				vec3_scale(ax[2], clamped.z))));
		delta = vec3_sub(pt, closest_on_box);
		dist_sq = vec3_mag_sq(delta);
		if (dist_sq < best_dist)
		{
			best_dist = dist_sq;
			best_pt = pt;
			best_box_pt = closest_on_box;
		}
		i++;
	}
	if (best_dist >= cap->radius * cap->radius)
		return (false);
	dist = sqrt(best_dist);
	delta = vec3_sub(best_pt, best_box_pt);
	if (dist < 1e-9)
		c->normal = vec3(0, 1, 0);
	else
		c->normal = vec3_scale(delta, 1.0 / dist);
	c->penetration = cap->radius - dist;
	c->a = &bx->phys;
	c->b = &cap->phys;
	c->ta = &bx->transform;
	c->tb = &cap->transform;
	c->contact_point = best_box_pt;
	c->ra = vec3_sub(best_box_pt, bx->phys.center);
	c->rb = vec3_sub(best_box_pt, cap->transform.pos);
	c->restitution = fmin(bx->phys.elasticity, cap->phys.elasticity);
	c->friction = sqrt(bx->phys.friction * cap->phys.friction);
	return (true);
}

/* ── vertex helpers: point inside sphere / capsule ──────────────────────── */

static bool	vertex_vs_sphere(t_vec3 v, t_sphere *sp,
		t_physics_body *pb, t_transform *tr, t_contact *c)
{
	t_vec3	delta;
	double	dist_sq;
	double	r;
	double	dist;

	r = sqrt(sp->radius_sq);
	delta = vec3_sub(v, sp->transform.pos);
	dist_sq = vec3_mag_sq(delta);
	if (dist_sq >= r * r)
		return (false);
	dist = sqrt(dist_sq);
	if (dist < 1e-9)
		c->normal = vec3(0, 1, 0);
	else
		c->normal = vec3_scale(delta, 1.0 / dist);
	c->penetration = r - dist;
	c->a = pb;
	c->b = &sp->phys;
	c->ta = tr;
	c->tb = &sp->transform;
	c->contact_point = v;
	c->ra = vec3_sub(v, pb->center);
	c->rb = vec3_sub(v, sp->transform.pos);
	c->restitution = fmin(pb->elasticity, sp->phys.elasticity);
	c->friction = sqrt(pb->friction * sp->phys.friction);
	return (true);
}

static bool	vertex_vs_capsule(t_vec3 v, t_capsule *cap,
		t_physics_body *pb, t_transform *tr, t_contact *c)
{
	t_vec3	p0;
	t_vec3	p1;
	t_vec3	closest;
	t_vec3	delta;
	double	dist_sq;
	double	dist;

	p0 = vec3_add(cap->transform.pos,
			vec3_scale(cap->axis, cap->half_height));
	p1 = vec3_sub(cap->transform.pos,
			vec3_scale(cap->axis, cap->half_height));
	closest = seg_closest(p0, p1, v);
	delta = vec3_sub(v, closest);
	dist_sq = vec3_mag_sq(delta);
	if (dist_sq >= cap->radius * cap->radius)
		return (false);
	dist = sqrt(dist_sq);
	if (dist < 1e-9)
		c->normal = vec3(0, 1, 0);
	else
		c->normal = vec3_scale(delta, 1.0 / dist);
	c->penetration = cap->radius - dist;
	c->a = pb;
	c->b = &cap->phys;
	c->ta = tr;
	c->tb = &cap->transform;
	c->contact_point = closest;
	c->ra = vec3_sub(closest, pb->center);
	c->rb = vec3_sub(closest, cap->transform.pos);
	c->restitution = fmin(pb->elasticity, cap->phys.elasticity);
	c->friction = sqrt(pb->friction * cap->phys.friction);
	return (true);
}

/* ── rect vs sphere / capsule ───────────────────────────────────────────── */

int	collide_rect_sphere(t_rect *rc, t_sphere *sp, t_contact *c, int max_c)
{
	t_contact	tmp;
	int			count;
	int			i;

	count = 0;
	i = 0;
	while (i < 4 && count < max_c)
	{
		if (vertex_vs_sphere(rc->v[i], sp, &rc->phys, &rc->transform, &tmp))
			c[count++] = tmp;
		i++;
	}
	return (count);
}

int	collide_rect_capsule(t_rect *rc, t_capsule *cap, t_contact *c, int max_c)
{
	t_contact	tmp;
	int			count;
	int			i;

	count = 0;
	i = 0;
	while (i < 4 && count < max_c)
	{
		if (vertex_vs_capsule(rc->v[i], cap, &rc->phys, &rc->transform, &tmp))
			c[count++] = tmp;
		i++;
	}
	return (count);
}

/* ── tri vs sphere / capsule ────────────────────────────────────────────── */

int	collide_tri_sphere(t_tri_shape *tr, t_sphere *sp, t_contact *c, int max_c)
{
	t_contact	tmp;
	int			count;
	int			i;

	count = 0;
	i = 0;
	while (i < 3 && count < max_c)
	{
		if (vertex_vs_sphere(tr->v[i], sp, &tr->phys, &tr->xform, &tmp))
			c[count++] = tmp;
		i++;
	}
	return (count);
}

int	collide_tri_capsule(t_tri_shape *tr, t_capsule *cap, t_contact *c,
		int max_c)
{
	t_contact	tmp;
	int			count;
	int			i;

	count = 0;
	i = 0;
	while (i < 3 && count < max_c)
	{
		if (vertex_vs_capsule(tr->v[i], cap, &tr->phys, &tr->xform, &tmp))
			c[count++] = tmp;
		i++;
	}
	return (count);
}

/* ── pyramid vs sphere / capsule ────────────────────────────────────────── */

int	collide_pyramid_sphere(t_pyramid *py, t_sphere *sp, t_contact *c,
		int max_c)
{
	t_vec3		verts[5];
	t_contact	tmp;
	int			count;
	int			i;

	pyramid_get_verts(py, verts);
	count = 0;
	i = 0;
	while (i < 5 && count < max_c)
	{
		if (vertex_vs_sphere(verts[i], sp, &py->phys, &py->transform, &tmp))
			c[count++] = tmp;
		i++;
	}
	return (count);
}

int	collide_pyramid_capsule(t_pyramid *py, t_capsule *cap, t_contact *c,
		int max_c)
{
	t_vec3		verts[5];
	t_contact	tmp;
	int			count;
	int			i;

	pyramid_get_verts(py, verts);
	count = 0;
	i = 0;
	while (i < 5 && count < max_c)
	{
		if (vertex_vs_capsule(verts[i], cap, &py->phys, &py->transform, &tmp))
			c[count++] = tmp;
		i++;
	}
	return (count);
}

/* ── cylinder vs sphere / capsule / box (cylinder treated as fat capsule) ── */

bool	collide_cylinder_sphere(t_cylinder *cy, t_sphere *sp, t_contact *c)
{
	t_vec3	ax;
	t_vec3	p0;
	t_vec3	p1;
	t_vec3	closest;
	t_vec3	delta;
	double	dist_sq;
	double	dist;
	double	r;
	double	r_sum;

	ax = vec3_norm(cy->transform.forward);
	p0 = cy->transform.pos;
	p1 = vec3_add(p0, vec3_scale(ax, cy->transform.scale.y));
	r = sqrt(sp->radius_sq);
	r_sum = cy->transform.scale.x + r;
	closest = seg_closest(p0, p1, sp->transform.pos);
	delta = vec3_sub(sp->transform.pos, closest);
	dist_sq = vec3_mag_sq(delta);
	if (dist_sq >= r_sum * r_sum)
		return (false);
	dist = sqrt(dist_sq);
	if (dist < 1e-9)
		c->normal = vec3(0, 1, 0);
	else
		c->normal = vec3_scale(delta, 1.0 / dist);
	c->penetration = r_sum - dist;
	c->a = &cy->phys;
	c->b = &sp->phys;
	c->ta = &cy->transform;
	c->tb = &sp->transform;
	c->contact_point = closest;
	c->ra = vec3_sub(closest, cy->phys.center);
	c->rb = vec3_sub(closest, sp->transform.pos);
	c->restitution = fmin(cy->phys.elasticity, sp->phys.elasticity);
	c->friction = sqrt(cy->phys.friction * sp->phys.friction);
	return (true);
}

bool	collide_cylinder_capsule(t_cylinder *cy, t_capsule *cap, t_contact *c)
{
	t_vec3	p0;
	t_vec3	p1;
	t_vec3	q0;
	t_vec3	q1;
	t_vec3	P;
	t_vec3	Q;
	t_vec3	delta;
	double	dist_sq;
	double	dist;
	double	r_sum;

	p0 = cy->transform.pos;
	p1 = vec3_add(p0, vec3_scale(vec3_norm(cy->transform.forward),
				cy->transform.scale.y));
	q0 = vec3_add(cap->transform.pos,
			vec3_scale(cap->axis, cap->half_height));
	q1 = vec3_sub(cap->transform.pos,
			vec3_scale(cap->axis, cap->half_height));
	seg_seg_closest(p0, p1, q0, q1, &P, &Q);
	delta = vec3_sub(P, Q);
	dist_sq = vec3_mag_sq(delta);
	r_sum = cy->transform.scale.x + cap->radius;
	if (dist_sq >= r_sum * r_sum)
		return (false);
	dist = sqrt(dist_sq);
	if (dist < 1e-9)
		c->normal = vec3(0, 1, 0);
	else
		c->normal = vec3_scale(delta, 1.0 / dist);
	c->penetration = r_sum - dist;
	c->a = &cy->phys;
	c->b = &cap->phys;
	c->ta = &cy->transform;
	c->tb = &cap->transform;
	c->contact_point = vec3_scale(vec3_add(P, Q), 0.5);
	c->ra = vec3_sub(c->contact_point, cy->phys.center);
	c->rb = vec3_sub(c->contact_point, cap->transform.pos);
	c->restitution = fmin(cy->phys.elasticity, cap->phys.elasticity);
	c->friction = sqrt(cy->phys.friction * cap->phys.friction);
	return (true);
}

bool	collide_cylinder_box(t_cylinder *cy, t_box *bx, t_contact *c)
{
	t_vec3	ax[3];
	t_vec3	p0;
	t_vec3	p1;
	t_vec3	pt;
	t_vec3	local;
	t_vec3	clamped;
	t_vec3	closest_on_box;
	t_vec3	delta;
	t_vec3	best_pt;
	t_vec3	best_box_pt;
	double	best_dist;
	double	dist_sq;
	double	dist;
	double	frac;
	double	r_cy;
	int		i;

	ax[0] = vec3_norm(bx->transform.forward);
	vec3_orthonormal_basis(ax[0], &ax[1], &ax[2]);
	p0 = cy->transform.pos;
	p1 = vec3_add(p0, vec3_scale(vec3_norm(cy->transform.forward),
				cy->transform.scale.y));
	r_cy = cy->transform.scale.x;
	best_dist = 1e30;
	best_pt = p0;
	best_box_pt = bx->phys.center;
	i = 0;
	while (i <= 4)
	{
		frac = i * 0.25;
		pt = vec3_add(vec3_scale(p0, 1.0 - frac), vec3_scale(p1, frac));
		local.x = vec3_dot(vec3_sub(pt, bx->phys.center), ax[0]);
		local.y = vec3_dot(vec3_sub(pt, bx->phys.center), ax[1]);
		local.z = vec3_dot(vec3_sub(pt, bx->phys.center), ax[2]);
		clamped.x = fmax(-bx->half_extents.x,
				fmin(bx->half_extents.x, local.x));
		clamped.y = fmax(-bx->half_extents.y,
				fmin(bx->half_extents.y, local.y));
		clamped.z = fmax(-bx->half_extents.z,
				fmin(bx->half_extents.z, local.z));
		closest_on_box = vec3_add(bx->phys.center,
				vec3_add(vec3_scale(ax[0], clamped.x),
				vec3_add(vec3_scale(ax[1], clamped.y),
				vec3_scale(ax[2], clamped.z))));
		delta = vec3_sub(pt, closest_on_box);
		dist_sq = vec3_mag_sq(delta);
		if (dist_sq < best_dist)
		{
			best_dist = dist_sq;
			best_pt = pt;
			best_box_pt = closest_on_box;
		}
		i++;
	}
	if (best_dist >= r_cy * r_cy)
		return (false);
	dist = sqrt(best_dist);
	delta = vec3_sub(best_pt, best_box_pt);
	if (dist < 1e-9)
		c->normal = vec3(0, 1, 0);
	else
		c->normal = vec3_scale(delta, 1.0 / dist);
	c->penetration = r_cy - dist;
	c->a = &cy->phys;
	c->b = &bx->phys;
	c->ta = &cy->transform;
	c->tb = &bx->transform;
	c->contact_point = best_box_pt;
	c->ra = vec3_sub(best_box_pt, cy->phys.center);
	c->rb = vec3_sub(best_box_pt, bx->phys.center);
	c->restitution = fmin(cy->phys.elasticity, bx->phys.elasticity);
	c->friction = sqrt(cy->phys.friction * bx->phys.friction);
	return (true);
}