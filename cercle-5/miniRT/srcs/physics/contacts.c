/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contacts.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 20:31:31 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/06 20:31:31 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"
#include "objects.h"
#include "scene.h"
#include "raytracing.h"
#include <semaphore.h>

/*
** GJK-based narrow phase for all convex shape pairs.
**
** The broadphase uses the existing BVH (for sphere vs sphere/mesh)
** plus per-type AABB overlap guards.  The actual collision test is
** always gjk_make_contact() or gjk_vs_plane(), replacing the old
** N^2 dispatch table in collide.c.
*/

static bool	aabb_overlap(t_aabb a, t_aabb b)
{
	if (a.max.x < b.min.x || a.min.x > b.max.x)
		return (false);
	if (a.max.y < b.min.y || a.min.y > b.max.y)
		return (false);
	if (a.max.z < b.min.z || a.min.z > b.max.z)
		return (false);
	return (true);
}

/*
** Analytic sphere vs capsule — replaces GJK for this pair.
** Normal points from sphere (A) toward capsule (B), matching solver convention.
*/
static int	sphere_vs_capsule(t_sphere *sp, t_capsule *cap, t_contact *c)
{
	t_vec3	p0;
	t_vec3	p1;
	t_vec3	seg;
	t_vec3	to_sp;
	t_vec3	closest;
	t_vec3	d;
	double	dist_sq;
	double	r_sum;
	double	dist;
	double	seg_len_sq;
	double	t;

	p0 = vec3_sub(cap->transform.pos, vec3_scale(cap->axis, cap->half_height));
	p1 = vec3_add(cap->transform.pos, vec3_scale(cap->axis, cap->half_height));
	seg = vec3_sub(p1, p0);
	to_sp = vec3_sub(sp->phys.center, p0);
	seg_len_sq = vec3_mag_sq(seg);
	if (seg_len_sq < 1e-12)
		closest = p0;
	else
	{
		t = vec3_dot(to_sp, seg) / seg_len_sq;
		if (t < 0.0)
			t = 0.0;
		if (t > 1.0)
			t = 1.0;
		closest = vec3_add(p0, vec3_scale(seg, t));
	}
	d = vec3_sub(sp->phys.center, closest);
	dist_sq = vec3_mag_sq(d);
	r_sum = sqrt(sp->radius_sq) + cap->radius;
	if (dist_sq >= r_sum * r_sum)
		return (0);
	dist = sqrt(dist_sq);
	/* Normal: from sphere (A) toward capsule (B) = -d/dist */
	c->normal = (dist > 1e-9)
		? vec3_scale(d, -1.0 / dist) : vec3(0, -1, 0);
	c->penetration = r_sum - dist;
	c->a = &sp->phys;
	c->b = &cap->phys;
	c->ta = &sp->transform;
	c->tb = &cap->transform;
	c->contact_point = vec3_add(sp->phys.center,
			vec3_scale(c->normal,
				sqrt(sp->radius_sq) - c->penetration * 0.5));
	c->ra = vec3_sub(c->contact_point, sp->phys.center);
	c->rb = vec3_sub(closest, cap->phys.center);
	c->restitution = fmin(sp->phys.elasticity, cap->phys.elasticity);
	c->friction = sqrt(sp->phys.friction * cap->phys.friction);
	return (1);
}

/*
** Multi-contact box vs plane: tests all 8 corners, generates one contact
** per corner that penetrates the plane.  Gives 1-4 stable contacts instead
** of the single-point EPA result, which prevents the box from rocking.
*/
static int	box_vs_plane(t_box *bx, t_plane *pl, t_contact *c, int max_c)
{
	t_vec3	n;
	t_vec3	ax[3];
	t_vec3	he;
	t_vec3	corner;
	t_vec3	to_corner;
	double	dist;
	int		count;
	int		i;
	int		sx;
	int		sy;
	int		sz;

	n = vec3_norm(pl->transform.up);
	ax[0] = vec3_norm(bx->transform.forward);
	vec3_orthonormal_basis(ax[0], &ax[1], &ax[2]);
	he = bx->half_extents;
	count = 0;
	i = 0;
	while (i < 8 && count < max_c)
	{
		sx = (i & 1) ? 1 : -1;
		sy = (i & 2) ? 1 : -1;
		sz = (i & 4) ? 1 : -1;
		corner = vec3_add(bx->phys.center,
				vec3_add(
					vec3_add(vec3_scale(ax[0], sx * he.x),
						vec3_scale(ax[1], sy * he.y)),
					vec3_scale(ax[2], sz * he.z)));
		to_corner = vec3_sub(corner, pl->transform.pos);
		dist = vec3_dot(to_corner, n);
		if (dist < 0.0)
		{
			c[count].normal = vec3_scale(n, -1.0);
			c[count].penetration = -dist;
			c[count].a = &bx->phys;
			c[count].b = NULL;
			c[count].ta = &bx->transform;
			c[count].tb = &pl->transform;
			c[count].contact_point = corner;
			c[count].ra = vec3_sub(corner, bx->phys.center);
			c[count].rb = vec3(0, 0, 0);
			c[count].restitution = fmin(bx->phys.elasticity, 0.5);
			c[count].friction = sqrt(bx->phys.friction * 0.5);
			count++;
		}
		i++;
	}
	return (count);
}

/*
** Multi-contact rect vs plane: tests all 4 pre-built world-space vertices.
*/
static int	rect_vs_plane(t_rect *rc, t_plane *pl, t_contact *c, int max_c)
{
	t_vec3	n;
	t_vec3	to_v;
	double	dist;
	int		count;
	int		i;

	n = vec3_norm(pl->transform.up);
	count = 0;
	i = 0;
	while (i < 4 && count < max_c)
	{
		to_v = vec3_sub(rc->v[i], pl->transform.pos);
		dist = vec3_dot(to_v, n);
		if (dist < 0.0)
		{
			c[count].normal = vec3_scale(n, -1.0);
			c[count].penetration = -dist;
			c[count].a = &rc->phys;
			c[count].b = NULL;
			c[count].ta = &rc->transform;
			c[count].tb = &pl->transform;
			c[count].contact_point = rc->v[i];
			c[count].ra = vec3_sub(rc->v[i], rc->phys.center);
			c[count].rb = vec3(0, 0, 0);
			c[count].restitution = fmin(rc->phys.elasticity, 0.5);
			c[count].friction = sqrt(rc->phys.friction * 0.5);
			count++;
		}
		i++;
	}
	return (count);
}

static int	tri_vs_plane(t_tri_shape *tr, t_plane *pl, t_contact *c,
				int max_c)
{
	t_vec3	n;
	t_vec3	to_v;
	double	dist;
	int			count;
	int			i;

	n = vec3_norm(pl->transform.up);
	count = 0;
	i = 0;
	while (i < 3 && count < max_c)
	{
		to_v = vec3_sub(tr->v[i], pl->transform.pos);
		dist = vec3_dot(to_v, n);
		if (dist < 0.0)
		{
			c[count].normal = vec3_scale(n, -1.0);
			c[count].penetration = -dist;
			c[count].a = &tr->phys;
			c[count].b = NULL;
			c[count].ta = &tr->xform;
			c[count].tb = &pl->transform;
			c[count].contact_point = tr->v[i];
			c[count].ra = vec3_sub(tr->v[i], tr->phys.center);
			c[count].rb = vec3(0, 0, 0);
			c[count].restitution = fmin(tr->phys.elasticity, 0.5);
			c[count].friction = sqrt(tr->phys.friction * 0.5);
			count++;
		}
		i++;
	}
	return (count);
}

static int	pyramid_vs_plane(t_pyramid *py, t_plane *pl, t_contact *c,
				int max_c)
{
	t_vec3	n;
	t_vec3	verts[5];
	t_vec3	ref;
	t_vec3	right;
	t_vec3	fwd;
	t_vec3	to_v;
	double	h;
	double	dist;
	int			count;
	int			i;

	n = vec3_norm(pl->transform.up);
	h = py->base_size * 0.5;
	if (fabs(py->up.y) < 0.9)
		ref = vec3(0, 1, 0);
	else
		ref = vec3(1, 0, 0);
	right = vec3_norm(vec3_cross(py->up, ref));
	fwd = vec3_cross(right, py->up);
	verts[0] = vec3_add(vec3_add(py->transform.pos,
				vec3_scale(right, h)), vec3_scale(fwd, h));
	verts[1] = vec3_add(vec3_add(py->transform.pos,
				vec3_scale(right, -h)), vec3_scale(fwd, h));
	verts[2] = vec3_add(vec3_add(py->transform.pos,
				vec3_scale(right, -h)), vec3_scale(fwd, -h));
	verts[3] = vec3_add(vec3_add(py->transform.pos,
				vec3_scale(right, h)), vec3_scale(fwd, -h));
	verts[4] = vec3_add(py->transform.pos,
			vec3_scale(py->up, py->height));
	count = 0;
	i = 0;
	while (i < 5 && count < max_c)
	{
		to_v = vec3_sub(verts[i], pl->transform.pos);
		dist = vec3_dot(to_v, n);
		if (dist < 0.0)
		{
			c[count].normal = vec3_scale(n, -1.0);
			c[count].penetration = -dist;
			c[count].a = &py->phys;
			c[count].b = NULL;
			c[count].ta = &py->transform;
			c[count].tb = &pl->transform;
			c[count].contact_point = verts[i];
			c[count].ra = vec3_sub(verts[i], py->phys.center);
			c[count].rb = vec3(0, 0, 0);
			c[count].restitution = fmin(py->phys.elasticity, 0.5);
			c[count].friction = sqrt(py->phys.friction * 0.5);
			count++;
		}
		i++;
	}
	return (count);
}

static int	check_leaf_ref(t_scene *s, t_sphere *sphere, int idx,
		t_bvh_ref ref, t_contact *c)
{
	t_sphere	*other;
	t_vec3		d;
	double		dist_sq;
	double		r_sum;

	if (ref.type == TYPE_SPHERE && ref.index > idx)
	{
		/* Fast analytic sphere–sphere — avoids GJK entirely */
		other = &s->spheres[ref.index];
		d = vec3_sub(sphere->phys.center, other->phys.center);
		dist_sq = vec3_mag_sq(d);
		r_sum = sqrt(sphere->radius_sq) + sqrt(other->radius_sq);
		if (dist_sq >= r_sum * r_sum)
			return (0);
		c->penetration = r_sum - sqrt(dist_sq);
		c->normal = (dist_sq > 1e-12)
			? vec3_scale(d, -1.0 / sqrt(dist_sq))
			: vec3(0, 1, 0);
		c->contact_point = vec3_add(sphere->phys.center,
				vec3_scale(c->normal, sqrt(sphere->radius_sq) - c->penetration * 0.5));
		c->a = &sphere->phys;
		c->b = &other->phys;
		c->ta = &sphere->transform;
		c->tb = &other->transform;
		c->ra = vec3_sub(c->contact_point, sphere->phys.center);
		c->rb = vec3_sub(c->contact_point, other->phys.center);
		c->restitution = fmin(sphere->phys.elasticity, other->phys.elasticity);
		c->friction = sqrt(sphere->phys.friction * other->phys.friction);
		return (1);
	}
	if (ref.type == TYPE_MESH)
	{
		t_mesh	*m;
		t_vec3	nrm;
		double	pen;

		m = &s->meshes[ref.index];
		if (!detect_sphere_mesh_collision(sphere, m, &nrm, &pen))
			return (0);
		c->a = &sphere->phys;
		c->ta = &sphere->transform;
		c->b = &m->phys;
		c->tb = &m->transform;
		c->normal = nrm;
		c->penetration = pen;
		c->restitution = (sphere->phys.elasticity + m->phys.elasticity) * 0.5;
		c->friction = (sphere->phys.friction + m->phys.friction) * 0.5;
		c->contact_point = vec3_add(sphere->phys.center,
				vec3_scale(nrm, sqrt(sphere->radius_sq) - pen));
		c->ra = vec3_sub(c->contact_point, sphere->phys.center);
		c->rb = vec3_sub(c->contact_point, m->phys.center);
		return (1);
	}
	return (0);
}

static int	check_leaf(t_scene *s, t_sphere *sp, int idx,
		const t_bvh *bvh, int node_idx, t_contact *c, int count, int max)
{
	const t_bvh_node	*node;
	int					i;
	int					end;

	node = &bvh->nodes[node_idx];
	i = node->left_or_first;
	end = i + node->count;
	while (i < end && count < max)
	{
		if (check_leaf_ref(s, sp, idx, bvh->refs[i], &c[count]))
			count++;
		i++;
	}
	return (count);
}

static int	traverse_bvh_contacts(t_scene *s, int idx, t_sphere *sp,
		t_aabb saabb, t_contact *c, int count, int max)
{
	int					stack[128];
	int					ptr;
	int					i;
	const t_bvh_node	*node;

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
			count = check_leaf(s, sp, idx, s->bvh, i, c, count, max);
		else if (ptr < 126)
		{
			stack[ptr++] = node->left_or_first;
			stack[ptr++] = i + 1;
		}
	}
	return (count);
}

/* Helper: test shape SA against all planes. */
static int	gjk_vs_all_planes(t_gjk_shape *sa, t_physics_body *ba,
		t_transform *ta, t_scene *s, t_contact *c, int count, int max)
{
	int	p;

	p = 0;
	while (p < s->plane_count && count < max)
	{
		count += gjk_vs_plane(sa, ba, ta, &s->planes[p], &c[count]);
		p++;
	}
	return (count);
}

static int	query_sphere(t_scene *s, int idx, t_contact *c, int count,
		int max)
{
	t_sphere	*sphere;
	t_aabb		saabb;
	t_aabb		other;
	t_gjk_shape	sa;
	t_gjk_shape	sb;
	int			p;

	sphere = &s->spheres[idx];
	if (sphere->phys.is_static)
		return (count);
	saabb = sphere_aabb(sphere);
	sa = (t_gjk_shape){sphere, gjk_support_sphere, sphere->phys.center};
	count = traverse_bvh_contacts(s, idx, sphere, saabb, c, count, max);
	count = gjk_vs_all_planes(&sa, &sphere->phys, &sphere->transform,
			s, c, count, max);
	p = 0;
	while (p < s->box_count && count < max)
	{
		other = box_aabb(&s->boxes[p]);
		if (aabb_overlap(saabb, other))
		{
			sb = (t_gjk_shape){&s->boxes[p], gjk_support_box,
				s->boxes[p].phys.center};
			count += gjk_make_contact(&sa, &sb,
					&sphere->phys, &s->boxes[p].phys,
					&sphere->transform, &s->boxes[p].transform, &c[count]);
		}
		p++;
	}
	p = 0;
	while (p < s->capsule_count && count < max)
	{
		other = capsule_aabb(&s->capsules[p]);
		if (aabb_overlap(saabb, other))
			count += sphere_vs_capsule(sphere, &s->capsules[p], &c[count]);
		p++;
	}
	p = 0;
	while (p < s->cylinder_count && count < max)
	{
		other = cylinder_aabb(&s->cylinders[p]);
		if (aabb_overlap(saabb, other))
		{
			sb = (t_gjk_shape){&s->cylinders[p], gjk_support_cylinder,
				s->cylinders[p].phys.center};
			count += gjk_make_contact(&sa, &sb,
					&sphere->phys, &s->cylinders[p].phys,
					&sphere->transform, &s->cylinders[p].transform, &c[count]);
		}
		p++;
	}
	p = 0;
	while (p < s->rect_count && count < max)
	{
		other = rect_aabb(&s->rects[p]);
		if (aabb_overlap(saabb, other))
		{
			sb = (t_gjk_shape){&s->rects[p], gjk_support_rect,
				s->rects[p].phys.center};
			count += gjk_make_contact(&sa, &sb,
					&sphere->phys, &s->rects[p].phys,
					&sphere->transform, &s->rects[p].transform, &c[count]);
		}
		p++;
	}
	p = 0;
	while (p < s->tri_count && count < max)
	{
		other = tri_shape_aabb(&s->tris[p]);
		if (aabb_overlap(saabb, other))
		{
			sb = (t_gjk_shape){&s->tris[p], gjk_support_tri,
				s->tris[p].phys.center};
			count += gjk_make_contact(&sa, &sb,
					&sphere->phys, &s->tris[p].phys,
					&sphere->transform, &s->tris[p].xform, &c[count]);
		}
		p++;
	}
	p = 0;
	while (p < s->pyramid_count && count < max)
	{
		other = pyramid_aabb(&s->pyramids[p]);
		if (aabb_overlap(saabb, other))
		{
			sb = (t_gjk_shape){&s->pyramids[p], gjk_support_pyramid,
				s->pyramids[p].phys.center};
			count += gjk_make_contact(&sa, &sb,
					&sphere->phys, &s->pyramids[p].phys,
					&sphere->transform, &s->pyramids[p].transform, &c[count]);
		}
		p++;
	}
	return (count);
}

static int	query_rect(t_scene *s, int idx, t_contact *c, int count, int max)
{
	t_rect		*rc;
	t_aabb		raabb;
	t_aabb		other;
	t_gjk_shape	sa;
	t_gjk_shape	sb;
	int			p;

	rc = &s->rects[idx];
	if (rc->phys.is_static)
		return (count);
	raabb = rect_aabb(rc);
	sa = (t_gjk_shape){rc, gjk_support_rect, rc->phys.center};
	p = 0;
	while (p < s->plane_count && count < max)
	{
		count += rect_vs_plane(rc, &s->planes[p], &c[count], max - count);
		p++;
	}
	p = idx + 1;
	while (p < s->rect_count && count < max)
	{
		other = rect_aabb(&s->rects[p]);
		if (aabb_overlap(raabb, other))
		{
			sb = (t_gjk_shape){&s->rects[p], gjk_support_rect,
				s->rects[p].phys.center};
			count += gjk_make_contact(&sa, &sb,
					&rc->phys, &s->rects[p].phys,
					&rc->transform, &s->rects[p].transform, &c[count]);
		}
		p++;
	}
	p = 0;
	while (p < s->tri_count && count < max)
	{
		other = tri_shape_aabb(&s->tris[p]);
		if (aabb_overlap(raabb, other))
		{
			sb = (t_gjk_shape){&s->tris[p], gjk_support_tri,
				s->tris[p].phys.center};
			count += gjk_make_contact(&sa, &sb,
					&rc->phys, &s->tris[p].phys,
					&rc->transform, &s->tris[p].xform, &c[count]);
		}
		p++;
	}
	p = 0;
	while (p < s->pyramid_count && count < max)
	{
		other = pyramid_aabb(&s->pyramids[p]);
		if (aabb_overlap(raabb, other))
		{
			sb = (t_gjk_shape){&s->pyramids[p], gjk_support_pyramid,
				s->pyramids[p].phys.center};
			count += gjk_make_contact(&sa, &sb,
					&rc->phys, &s->pyramids[p].phys,
					&rc->transform, &s->pyramids[p].transform, &c[count]);
		}
		p++;
	}
	return (count);
}

static int	query_pyramid(t_scene *s, int idx, t_contact *c, int count,
		int max)
{
	t_pyramid	*py;
	t_aabb		pyaabb;
	t_aabb		other;
	t_gjk_shape	sa;
	t_gjk_shape	sb;
	int			p;

	py = &s->pyramids[idx];
	if (py->phys.is_static)
		return (count);
	pyaabb = pyramid_aabb(py);
	sa = (t_gjk_shape){py, gjk_support_pyramid, py->phys.center};
	p = 0;
	while (p < s->plane_count && count < max)
	{
		count += pyramid_vs_plane(py, &s->planes[p], &c[count], max - count);
		p++;
	}
	p = idx + 1;
	while (p < s->pyramid_count && count < max)
	{
		other = pyramid_aabb(&s->pyramids[p]);
		if (aabb_overlap(pyaabb, other))
		{
			sb = (t_gjk_shape){&s->pyramids[p], gjk_support_pyramid,
				s->pyramids[p].phys.center};
			count += gjk_make_contact(&sa, &sb,
					&py->phys, &s->pyramids[p].phys,
					&py->transform, &s->pyramids[p].transform, &c[count]);
		}
		p++;
	}
	return (count);
}

static int	query_box(t_scene *s, int idx, t_contact *c, int count, int max)
{
	t_box		*bx;
	t_aabb		baabb;
	t_aabb		other;
	t_gjk_shape	sa;
	t_gjk_shape	sb;
	int			p;

	bx = &s->boxes[idx];
	if (bx->phys.is_static)
		return (count);
	baabb = box_aabb(bx);
	sa = (t_gjk_shape){bx, gjk_support_box, bx->phys.center};
	p = 0;
	while (p < s->plane_count && count < max)
	{
		count += box_vs_plane(bx, &s->planes[p], &c[count], max - count);
		p++;
	}
	p = idx + 1;
	while (p < s->box_count && count < max)
	{
		other = box_aabb(&s->boxes[p]);
		if (aabb_overlap(baabb, other))
		{
			sb = (t_gjk_shape){&s->boxes[p], gjk_support_box,
				s->boxes[p].phys.center};
			count += gjk_make_contact(&sa, &sb,
					&bx->phys, &s->boxes[p].phys,
					&bx->transform, &s->boxes[p].transform, &c[count]);
		}
		p++;
	}
	p = 0;
	while (p < s->capsule_count && count < max)
	{
		other = capsule_aabb(&s->capsules[p]);
		if (aabb_overlap(baabb, other))
		{
			sb = (t_gjk_shape){&s->capsules[p], gjk_support_capsule,
				s->capsules[p].phys.center};
			count += gjk_make_contact(&sa, &sb,
					&bx->phys, &s->capsules[p].phys,
					&bx->transform, &s->capsules[p].transform, &c[count]);
		}
		p++;
	}
	p = 0;
	while (p < s->cylinder_count && count < max)
	{
		other = cylinder_aabb(&s->cylinders[p]);
		if (aabb_overlap(baabb, other))
		{
			sb = (t_gjk_shape){&s->cylinders[p], gjk_support_cylinder,
				s->cylinders[p].phys.center};
			count += gjk_make_contact(&sa, &sb,
					&bx->phys, &s->cylinders[p].phys,
					&bx->transform, &s->cylinders[p].transform, &c[count]);
		}
		p++;
	}
	p = 0;
	while (p < s->rect_count && count < max)
	{
		other = rect_aabb(&s->rects[p]);
		if (aabb_overlap(baabb, other))
		{
			sb = (t_gjk_shape){&s->rects[p], gjk_support_rect,
				s->rects[p].phys.center};
			count += gjk_make_contact(&sa, &sb,
					&bx->phys, &s->rects[p].phys,
					&bx->transform, &s->rects[p].transform, &c[count]);
		}
		p++;
	}
	p = 0;
	while (p < s->tri_count && count < max)
	{
		other = tri_shape_aabb(&s->tris[p]);
		if (aabb_overlap(baabb, other))
		{
			sb = (t_gjk_shape){&s->tris[p], gjk_support_tri,
				s->tris[p].phys.center};
			count += gjk_make_contact(&sa, &sb,
					&bx->phys, &s->tris[p].phys,
					&bx->transform, &s->tris[p].xform, &c[count]);
		}
		p++;
	}
	p = 0;
	while (p < s->pyramid_count && count < max)
	{
		other = pyramid_aabb(&s->pyramids[p]);
		if (aabb_overlap(baabb, other))
		{
			sb = (t_gjk_shape){&s->pyramids[p], gjk_support_pyramid,
				s->pyramids[p].phys.center};
			count += gjk_make_contact(&sa, &sb,
					&bx->phys, &s->pyramids[p].phys,
					&bx->transform, &s->pyramids[p].transform, &c[count]);
		}
		p++;
	}
	return (count);
}

static int	query_capsule(t_scene *s, int idx, t_contact *c, int count,
		int max)
{
	t_capsule	*cap;
	t_aabb		caabb;
	t_aabb		other;
	t_gjk_shape	sa;
	t_gjk_shape	sb;
	int			p;

	cap = &s->capsules[idx];
	if (cap->phys.is_static)
		return (count);
	caabb = capsule_aabb(cap);
	sa = (t_gjk_shape){cap, gjk_support_capsule, cap->phys.center};
	p = 0;
	while (p < s->plane_count && count < max)
	{
		count += gjk_vs_plane(&sa, &cap->phys, &cap->transform,
				&s->planes[p], &c[count]);
		p++;
	}
	p = idx + 1;
	while (p < s->capsule_count && count < max)
	{
		other = capsule_aabb(&s->capsules[p]);
		if (aabb_overlap(caabb, other))
		{
			sb = (t_gjk_shape){&s->capsules[p], gjk_support_capsule,
				s->capsules[p].phys.center};
			count += gjk_make_contact(&sa, &sb,
					&cap->phys, &s->capsules[p].phys,
					&cap->transform, &s->capsules[p].transform, &c[count]);
		}
		p++;
	}
	p = 0;
	while (p < s->cylinder_count && count < max)
	{
		other = cylinder_aabb(&s->cylinders[p]);
		if (aabb_overlap(caabb, other))
		{
			sb = (t_gjk_shape){&s->cylinders[p], gjk_support_cylinder,
				s->cylinders[p].phys.center};
			count += gjk_make_contact(&sa, &sb,
					&cap->phys, &s->cylinders[p].phys,
					&cap->transform, &s->cylinders[p].transform, &c[count]);
		}
		p++;
	}
	p = 0;
	while (p < s->rect_count && count < max)
	{
		other = rect_aabb(&s->rects[p]);
		if (aabb_overlap(caabb, other))
		{
			sb = (t_gjk_shape){&s->rects[p], gjk_support_rect,
				s->rects[p].phys.center};
			count += gjk_make_contact(&sa, &sb,
					&cap->phys, &s->rects[p].phys,
					&cap->transform, &s->rects[p].transform, &c[count]);
		}
		p++;
	}
	p = 0;
	while (p < s->tri_count && count < max)
	{
		other = tri_shape_aabb(&s->tris[p]);
		if (aabb_overlap(caabb, other))
		{
			sb = (t_gjk_shape){&s->tris[p], gjk_support_tri,
				s->tris[p].phys.center};
			count += gjk_make_contact(&sa, &sb,
					&cap->phys, &s->tris[p].phys,
					&cap->transform, &s->tris[p].xform, &c[count]);
		}
		p++;
	}
	p = 0;
	while (p < s->pyramid_count && count < max)
	{
		other = pyramid_aabb(&s->pyramids[p]);
		if (aabb_overlap(caabb, other))
		{
			sb = (t_gjk_shape){&s->pyramids[p], gjk_support_pyramid,
				s->pyramids[p].phys.center};
			count += gjk_make_contact(&sa, &sb,
					&cap->phys, &s->pyramids[p].phys,
					&cap->transform, &s->pyramids[p].transform, &c[count]);
		}
		p++;
	}
	return (count);
}

static int	query_tri(t_scene *s, int idx, t_contact *c, int count, int max)
{
	t_tri_shape	*tr;
	t_aabb		taabb;
	t_aabb		other;
	t_gjk_shape	sa;
	t_gjk_shape	sb;
	int			p;

	tr = &s->tris[idx];
	if (tr->phys.is_static)
		return (count);
	taabb = tri_shape_aabb(tr);
	sa = (t_gjk_shape){tr, gjk_support_tri, tr->phys.center};
	p = 0;
	while (p < s->plane_count && count < max)
	{
		count += tri_vs_plane(tr, &s->planes[p], &c[count], max - count);
		p++;
	}
	p = idx + 1;
	while (p < s->tri_count && count < max)
	{
		other = tri_shape_aabb(&s->tris[p]);
		if (aabb_overlap(taabb, other))
		{
			sb = (t_gjk_shape){&s->tris[p], gjk_support_tri,
				s->tris[p].phys.center};
			count += gjk_make_contact(&sa, &sb,
					&tr->phys, &s->tris[p].phys,
					&tr->xform, &s->tris[p].xform, &c[count]);
		}
		p++;
	}
	p = 0;
	while (p < s->pyramid_count && count < max)
	{
		other = pyramid_aabb(&s->pyramids[p]);
		if (aabb_overlap(taabb, other))
		{
			sb = (t_gjk_shape){&s->pyramids[p], gjk_support_pyramid,
				s->pyramids[p].phys.center};
			count += gjk_make_contact(&sa, &sb,
					&tr->phys, &s->pyramids[p].phys,
					&tr->xform, &s->pyramids[p].transform, &c[count]);
		}
		p++;
	}
	return (count);
}

static int	query_cylinder(t_scene *s, int idx, t_contact *c, int count,
		int max)
{
	t_cylinder	*cy;
	t_aabb		cyaabb;
	t_aabb		other;
	t_gjk_shape	sa;
	t_gjk_shape	sb;
	int			p;

	cy = &s->cylinders[idx];
	if (cy->phys.is_static)
		return (count);
	cyaabb = cylinder_aabb(cy);
	sa = (t_gjk_shape){cy, gjk_support_cylinder, cy->phys.center};
	count = gjk_vs_all_planes(&sa, &cy->phys, &cy->transform,
			s, c, count, max);
	p = idx + 1;
	while (p < s->cylinder_count && count < max)
	{
		other = cylinder_aabb(&s->cylinders[p]);
		if (aabb_overlap(cyaabb, other))
		{
			sb = (t_gjk_shape){&s->cylinders[p], gjk_support_cylinder,
				s->cylinders[p].phys.center};
			count += gjk_make_contact(&sa, &sb,
					&cy->phys, &s->cylinders[p].phys,
					&cy->transform, &s->cylinders[p].transform, &c[count]);
		}
		p++;
	}
	p = 0;
	while (p < s->rect_count && count < max)
	{
		other = rect_aabb(&s->rects[p]);
		if (aabb_overlap(cyaabb, other))
		{
			sb = (t_gjk_shape){&s->rects[p], gjk_support_rect,
				s->rects[p].phys.center};
			count += gjk_make_contact(&sa, &sb,
					&cy->phys, &s->rects[p].phys,
					&cy->transform, &s->rects[p].transform, &c[count]);
		}
		p++;
	}
	p = 0;
	while (p < s->tri_count && count < max)
	{
		other = tri_shape_aabb(&s->tris[p]);
		if (aabb_overlap(cyaabb, other))
		{
			sb = (t_gjk_shape){&s->tris[p], gjk_support_tri,
				s->tris[p].phys.center};
			count += gjk_make_contact(&sa, &sb,
					&cy->phys, &s->tris[p].phys,
					&cy->transform, &s->tris[p].xform, &c[count]);
		}
		p++;
	}
	p = 0;
	while (p < s->pyramid_count && count < max)
	{
		other = pyramid_aabb(&s->pyramids[p]);
		if (aabb_overlap(cyaabb, other))
		{
			sb = (t_gjk_shape){&s->pyramids[p], gjk_support_pyramid,
				s->pyramids[p].phys.center};
			count += gjk_make_contact(&sa, &sb,
					&cy->phys, &s->pyramids[p].phys,
					&cy->transform, &s->pyramids[p].transform, &c[count]);
		}
		p++;
	}
	return (count);
}

# define PHYS_NUM_TYPES	7

typedef struct s_gen_job
{
	t_scene		*scene;
	t_contact	*out;
	int			max_c;
	int			count;
	int			type;
}	t_gen_job;

/*
** Persistent thread pool — workers created once, sleep on semaphores.
** One worker per type group; replaces the per-call pthread_create/join
** that cost 10-50 us each and dominated physics time for small scenes.
*/
typedef struct s_phys_pool
{
	pthread_t	threads[PHYS_NUM_TYPES];
	t_gen_job	jobs[PHYS_NUM_TYPES];
	int			indices[PHYS_NUM_TYPES];
	sem_t		start[PHYS_NUM_TYPES];
	sem_t		done[PHYS_NUM_TYPES];
	int			shutdown;
	int			initialized;
}	t_phys_pool;

static t_phys_pool	g_phys_pool;

static void	run_contact_job(t_gen_job *job)
{
	int	i;

	i = 0;
	if (job->type == 0)
		while (i < job->scene->sphere_count)
			job->count = query_sphere(job->scene, i++, job->out,
					job->count, job->max_c);
	else if (job->type == 1)
		while (i < job->scene->box_count)
			job->count = query_box(job->scene, i++, job->out,
					job->count, job->max_c);
	else if (job->type == 2)
		while (i < job->scene->capsule_count)
			job->count = query_capsule(job->scene, i++, job->out,
					job->count, job->max_c);
	else if (job->type == 3)
		while (i < job->scene->cylinder_count)
			job->count = query_cylinder(job->scene, i++, job->out,
					job->count, job->max_c);
	else if (job->type == 4)
		while (i < job->scene->rect_count)
			job->count = query_rect(job->scene, i++, job->out,
					job->count, job->max_c);
	else if (job->type == 5)
		while (i < job->scene->tri_count)
			job->count = query_tri(job->scene, i++, job->out,
					job->count, job->max_c);
	else
		while (i < job->scene->pyramid_count)
			job->count = query_pyramid(job->scene, i++, job->out,
					job->count, job->max_c);
}

static void	*pool_worker(void *arg)
{
	int	*idx;

	idx = (int *)arg;
	while (1)
	{
		sem_wait(&g_phys_pool.start[*idx]);
		if (g_phys_pool.shutdown)
		{
			sem_post(&g_phys_pool.done[*idx]);
			return (NULL);
		}
		run_contact_job(&g_phys_pool.jobs[*idx]);
		sem_post(&g_phys_pool.done[*idx]);
	}
}

static void	init_phys_pool(void)
{
	int	i;

	i = 0;
	while (i < PHYS_NUM_TYPES)
	{
		g_phys_pool.indices[i] = i;
		sem_init(&g_phys_pool.start[i], 0, 0);
		sem_init(&g_phys_pool.done[i], 0, 0);
		pthread_create(&g_phys_pool.threads[i], NULL,
			pool_worker, &g_phys_pool.indices[i]);
		i++;
	}
	g_phys_pool.initialized = 1;
}

int	generate_contacts(t_scene *scene, t_contact *contacts, int max_c)
{
	static t_contact	bufs[PHYS_NUM_TYPES][MAX_CONTACTS];
	int					count;
	int					t;
	int					n;

	if (!g_phys_pool.initialized)
		init_phys_pool();
	t = 0;
	while (t < PHYS_NUM_TYPES)
	{
		g_phys_pool.jobs[t] = (t_gen_job){scene, bufs[t], max_c, 0, t};
		sem_post(&g_phys_pool.start[t]);
		t++;
	}
	count = 0;
	t = 0;
	while (t < PHYS_NUM_TYPES)
	{
		sem_wait(&g_phys_pool.done[t]);
		n = g_phys_pool.jobs[t].count;
		if (count + n > max_c)
			n = max_c - count;
		if (n > 0)
			memcpy(&contacts[count], bufs[t], sizeof(t_contact) * n);
		count += n;
		t++;
	}
	return (count);
}

