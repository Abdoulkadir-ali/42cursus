/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   surface.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 11:37:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/09 23:57:57 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

/*
** closest_pt_tri: Ericson closest point on a triangle (a, b, c) to point p.
*/
static t_vec3	closest_pt_tri(t_vec3 p, t_vec3 a, t_vec3 b, t_vec3 c)
{
	t_vec3	ab;
	t_vec3	ac;
	t_vec3	ap;
	double	d[6];
	double	va;
	double	vb;
	double	vc;
	double	denom;

	ab = vec3_sub(b, a);
	ac = vec3_sub(c, a);
	ap = vec3_sub(p, a);
	d[0] = vec3_dot(ab, ap);
	d[1] = vec3_dot(ac, ap);
	if (d[0] <= 0.0 && d[1] <= 0.0)
		return (a);
	d[2] = vec3_dot(ab, vec3_sub(p, b));
	d[3] = vec3_dot(ac, vec3_sub(p, b));
	if (d[2] >= 0.0 && d[3] <= d[2])
		return (b);
	d[4] = vec3_dot(ab, vec3_sub(p, c));
	d[5] = vec3_dot(ac, vec3_sub(p, c));
	if (d[5] >= 0.0 && d[4] <= d[5])
		return (c);
	vc = d[0] * d[3] - d[2] * d[1];
	if (vc <= 0.0 && d[0] >= 0.0 && d[2] <= 0.0)
		return (vec3_add(a, vec3_scale(ab, d[0] / (d[0] - d[2]))));
	vb = d[4] * d[1] - d[0] * d[5];
	if (vb <= 0.0 && d[1] >= 0.0 && d[5] <= 0.0)
		return (vec3_add(a, vec3_scale(ac, d[1] / (d[1] - d[5]))));
	va = d[2] * d[5] - d[4] * d[3];
	if (va <= 0.0 && (d[3] - d[2]) >= 0.0 && (d[4] - d[5]) >= 0.0)
		return (vec3_add(b, vec3_scale(vec3_sub(c, b),
					(d[3] - d[2]) / ((d[3] - d[2]) + (d[4] - d[5])))));
	denom = 1.0 / (va + vb + vc);
	return (vec3_add(a, vec3_add(vec3_scale(ab, vb * denom),
				vec3_scale(ac, vc * denom))));
}

/*
** closest_pt_rect: closest point on a rectangle defined by corners v0-v3.
** v0→v1 is one axis, v0→v3 is the other (must be orthogonal for exact result).
*/
static t_vec3	closest_pt_rect(t_vec3 p, t_vec3 v0, t_vec3 v1, t_vec3 v3)
{
	t_vec3	e0;
	t_vec3	e1;
	t_vec3	d;
	double	s;
	double	t;

	e0 = vec3_sub(v1, v0);
	e1 = vec3_sub(v3, v0);
	d = vec3_sub(p, v0);
	s = fmax(0.0, fmin(1.0, vec3_dot(d, e0) / vec3_dot(e0, e0)));
	t = fmax(0.0, fmin(1.0, vec3_dot(d, e1) / vec3_dot(e1, e1)));
	return (vec3_add(v0, vec3_add(vec3_scale(e0, s), vec3_scale(e1, t))));
}

static void	em_py(t_shading *sha, t_scene *sc, t_vec3 *total,
				t_emissive_ref ref)
{
	t_pyramid	*py;

	py = &sc->pyramids[ref.index];
	sha->aux_v = vec3_sub(py->transform.pos, sha->hit->point);
	sha->em_normal = vec3(0, 0, 0);
	apply_em(sha, total, &sc->materials[py->mat_id], py->base_size * 0.5);
}

void	em_surf(t_shading *sha, t_scene *sc, t_vec3 *total,
				t_emissive_ref ref)
{
	t_tri_shape	*tr;
	t_rect		*rc;
	t_vec3		closest;
	double		e0_len;
	double		e1_len;

	if (ref.type == TYPE_TRI)
	{
		tr = &sc->tris[ref.index];
		closest = closest_pt_tri(sha->hit->point,
				tr->v[0], tr->v[1], tr->v[2]);
		sha->aux_v = vec3_sub(closest, sha->hit->point);
		sha->em_normal = tr->normal;
		apply_em(sha, total, &sc->materials[tr->mat_id], 0.5);
	}
	else if (ref.type == TYPE_RECT)
	{
		rc = &sc->rects[ref.index];
		closest = closest_pt_rect(sha->hit->point,
				rc->v[0], rc->v[1], rc->v[3]);
		e0_len = vec3_mag(vec3_sub(rc->v[1], rc->v[0]));
		e1_len = vec3_mag(vec3_sub(rc->v[3], rc->v[0]));
		sha->aux_v = vec3_sub(closest, sha->hit->point);
		sha->em_normal = rc->normal;
		apply_em(sha, total, &sc->materials[rc->mat_id],
			fmax(e0_len, e1_len) * 0.5);
	}
	else if (ref.type == TYPE_PYRAMID)
		em_py(sha, sc, total, ref);
}
