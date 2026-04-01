/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 20:31:31 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/01 12:51:15 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/*
** GJK support functions — return the point in each shape that is furthest
** along direction 'dir' (world space).  The function pointer is stored in
** t_gjk_shape so the GJK/EPA loop is shape-agnostic.
*/

t_vec3	gjk_support_sphere(const void *data, t_vec3 dir)
{
	const t_sphere	*sp;
	t_vec3			nd;
	double			len;

	sp = (const t_sphere *)data;
	len = vec3_mag(dir);
	if (len < 1e-9)
		return (sp->transform.pos);
	nd = vec3_scale(dir, 1.0 / len);
	return (vec3_add(sp->transform.pos, vec3_scale(nd, sqrt(sp->radius_sq))));
}

t_vec3	gjk_support_box(const void *data, t_vec3 dir)
{
	const t_box	*bx;
	t_vec3		ax[3];
	t_vec3		p;

	bx = (const t_box *)data;
	ax[0] = vec3_norm(bx->transform.forward);
	vec3_orthonormal_basis(ax[0], &ax[1], &ax[2]);
	p = bx->phys.center;
	if (vec3_dot(ax[0], dir) >= 0.0)
		p = vec3_add(p, vec3_scale(ax[0], bx->half_extents.x));
	else
		p = vec3_sub(p, vec3_scale(ax[0], bx->half_extents.x));
	if (vec3_dot(ax[1], dir) >= 0.0)
		p = vec3_add(p, vec3_scale(ax[1], bx->half_extents.y));
	else
		p = vec3_sub(p, vec3_scale(ax[1], bx->half_extents.y));
	if (vec3_dot(ax[2], dir) >= 0.0)
		p = vec3_add(p, vec3_scale(ax[2], bx->half_extents.z));
	else
		p = vec3_sub(p, vec3_scale(ax[2], bx->half_extents.z));
	return (p);
}

t_vec3	gjk_support_capsule(const void *data, t_vec3 dir)
{
	const t_capsule	*cap;
	t_vec3			pole;
	t_vec3			nd;
	double			len;

	cap = (const t_capsule *)data;
	if (vec3_dot(cap->axis, dir) >= 0.0)
		pole = vec3_add(cap->transform.pos,
				vec3_scale(cap->axis, cap->half_height));
	else
		pole = vec3_sub(cap->transform.pos,
				vec3_scale(cap->axis, cap->half_height));
	len = vec3_mag(dir);
	if (len < 1e-9)
		return (pole);
	nd = vec3_scale(dir, 1.0 / len);
	return (vec3_add(pole, vec3_scale(nd, cap->radius)));
}

/*
** Cylinder: transform.pos is the BOTTOM BASE, phys.center is the mid.
** axis = forward, radius = scale.x, height = scale.y.
** Support = lateral disk extreme + axial cap choice.
*/
t_vec3	gjk_support_cylinder(const void *data, t_vec3 dir)
{
	const t_cylinder	*cy;
	t_vec3				ax;
	t_vec3				lateral;
	t_vec3				center;
	double				axial_dot;
	double				lat_len;
	double				radius;

	cy = (const t_cylinder *)data;
	radius = cy->transform.scale.x;
	ax = vec3_norm(cy->transform.forward);
	center = cy->phys.center;
	axial_dot = vec3_dot(ax, dir);
	lateral = vec3_sub(dir, vec3_scale(ax, axial_dot));
	lat_len = vec3_mag(lateral);
	if (lat_len > 1e-9)
		lateral = vec3_scale(lateral, radius / lat_len);
	else
		lateral = vec3(0, 0, 0);
	if (axial_dot >= 0.0)
		return (vec3_add(vec3_add(center,
					vec3_scale(ax, cy->transform.scale.y * 0.5)), lateral));
	return (vec3_add(vec3_sub(center,
				vec3_scale(ax, cy->transform.scale.y * 0.5)), lateral));
}

/* Rect: 4 pre-built world-space verts; just max-dot. */
t_vec3	gjk_support_rect(const void *data, t_vec3 dir)
{
	const t_rect	*rc;
	t_vec3			best;
	double			best_d;
	double			d;
	int				i;

	rc = (const t_rect *)data;
	best = rc->v[0];
	best_d = vec3_dot(rc->v[0], dir);
	i = 1;
	while (i < 4)
	{
		d = vec3_dot(rc->v[i], dir);
		if (d > best_d)
		{
			best_d = d;
			best = rc->v[i];
		}
		i++;
	}
	return (best);
}

/* Triangle: 3 pre-built world-space verts. */
t_vec3	gjk_support_tri(const void *data, t_vec3 dir)
{
	const t_tri_shape	*tr;
	t_vec3				best;
	double				best_d;
	double				d;
	int					i;

	tr = (const t_tri_shape *)data;
	best = tr->v[0];
	best_d = vec3_dot(tr->v[0], dir);
	i = 1;
	while (i < 3)
	{
		d = vec3_dot(tr->v[i], dir);
		if (d > best_d)
		{
			best_d = d;
			best = tr->v[i];
		}
		i++;
	}
	return (best);
}

/* Pyramid: compute the 5 world-space verts on the fly, then max-dot. */
t_vec3	gjk_support_pyramid(const void *data, t_vec3 dir)
{
	const t_pyramid	*py;
	t_vec3			verts[5];
	t_vec3			ref;
	t_vec3			right;
	t_vec3			fwd;
	t_vec3			best;
	double			h;
	double			best_d;
	double			d;
	int				i;

	py = (const t_pyramid *)data;
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
	verts[4] = vec3_add(py->transform.pos, vec3_scale(py->up, py->height));
	best = verts[0];
	best_d = vec3_dot(verts[0], dir);
	i = 1;
	while (i < 5)
	{
		d = vec3_dot(verts[i], dir);
		if (d > best_d)
		{
			best_d = d;
			best = verts[i];
		}
		i++;
	}
	return (best);
}

/* Mesh: linear scan over all vertices (hull subset used by caller). */
t_vec3	gjk_support_mesh(const void *data, t_vec3 dir)
{
	const t_mesh	*m;
	t_vec3			best;
	double			best_d;
	double			d;
	int				i;

	m = (const t_mesh *)data;
	if (!m->vertices || m->vertex_count == 0)
		return (vec3(0, 0, 0));
	best = m->vertices[0].pos;
	best_d = vec3_dot(m->vertices[0].pos, dir);
	i = 1;
	while (i < m->vertex_count)
	{
		d = vec3_dot(m->vertices[i].pos, dir);
		if (d > best_d)
		{
			best_d = d;
			best = m->vertices[i].pos;
		}
		i++;
	}
	return (best);
}
