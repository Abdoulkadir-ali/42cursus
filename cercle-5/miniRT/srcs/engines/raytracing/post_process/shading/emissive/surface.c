/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   surface.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 11:37:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/14 11:55:07 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

t_vec3	closest_pt_rect(t_vec3 p, t_vec3 v0, t_vec3 v1, t_vec3 v2)
{
	t_vec3	d;
	t_vec3	e[2];
	double	u[2];

	d = vec3_sub(p, v0);
	e[0] = vec3_sub(v1, v0);
	e[1] = vec3_sub(v2, v0);
	u[0] = vec3_dot(d, e[0]) / (vec3_mag_sq(e[0]) + 1e-9);
	u[1] = vec3_dot(d, e[1]) / (vec3_mag_sq(e[1]) + 1e-9);
	if (u[0] < 0.0)
		u[0] = 0.0;
	if (u[0] > 1.0)
		u[0] = 1.0;
	if (u[1] < 0.0)
		u[1] = 0.0;
	if (u[1] > 1.0)
		u[1] = 1.0;
	return (vec3_add(v0, vec3_add(vec3_scale(e[0], u[0]),
				vec3_scale(e[1], u[1]))));
}

/*
** cpt_tri_edg: handles vertex/edge_AB/edge_AC regions;
**              returns zero vec3 for edge_BC or face case.
** closest_pt_tri: calls cpt_tri_edg then handles edge_BC and face.
*/
static t_vec3	cpt_tri_edg(t_vec3 p, t_vec3 a, t_vec3 b, t_vec3 c)
{
	t_vec3	v[2];
	double	d[6];

	v[0] = vec3_sub(b, a);
	v[1] = vec3_sub(c, a);
	d[0] = vec3_dot(v[0], vec3_sub(p, a));
	d[1] = vec3_dot(v[1], vec3_sub(p, a));
	if (d[0] <= 0.0 && d[1] <= 0.0)
		return (a);
	d[2] = vec3_dot(v[0], vec3_sub(p, b));
	d[3] = vec3_dot(v[1], vec3_sub(p, b));
	if (d[2] >= 0.0 && d[3] <= d[2])
		return (b);
	d[4] = vec3_dot(v[0], vec3_sub(p, c));
	d[5] = vec3_dot(v[1], vec3_sub(p, c));
	if (d[5] >= 0.0 && d[4] <= d[5])
		return (c);
	if (d[0] * d[3] - d[2] * d[1] <= 0.0 && d[0] >= 0.0 && d[2] <= 0.0)
		return (vec3_add(a, vec3_scale(v[0], d[0] / (d[0] - d[2]))));
	if (d[4] * d[1] - d[0] * d[5] <= 0.0 && d[1] >= 0.0 && d[5] <= 0.0)
		return (vec3_add(a, vec3_scale(v[1], d[1] / (d[1] - d[5]))));
	return (vec3(0, 0, 0));
}

t_vec3	closest_pt_tri(t_vec3 p, t_vec3 a, t_vec3 b, t_vec3 c)
{
	t_vec3	pt;
	t_vec3	v[2];
	double	d[6];
	double	den;

	pt = cpt_tri_edg(p, a, b, c);
	if (vec3_mag_sq(pt) > 1e-12)
		return (pt);
	v[0] = vec3_sub(b, a);
	v[1] = vec3_sub(c, a);
	d[0] = vec3_dot(v[0], vec3_sub(p, a));
	d[1] = vec3_dot(v[1], vec3_sub(p, a));
	d[2] = vec3_dot(v[0], vec3_sub(p, b));
	d[3] = vec3_dot(v[1], vec3_sub(p, b));
	d[4] = vec3_dot(v[0], vec3_sub(p, c));
	d[5] = vec3_dot(v[1], vec3_sub(p, c));
	if (d[2] * d[5] - d[4] * d[3] <= 0.0 && (d[3] - d[2]) >= 0.0
		&& (d[4] - d[5]) >= 0.0)
		return (vec3_add(b, vec3_scale(vec3_sub(c, b),
					(d[3] - d[2]) / ((d[3] - d[2]) + (d[4] - d[5])))));
	den = 1.0 / (d[2] * d[5] - d[4] * d[3] + d[4] * d[1] - d[0] * d[5]
			+ d[0] * d[3] - d[2] * d[1]);
	return (vec3_add(a, vec3_add(vec3_scale(v[0], (d[4] * d[1] - d[0] * d[5])
					* den), vec3_scale(v[1], (d[0] * d[3] - d[2] * d[1])
					* den))));
}

void	em_tri(t_shading *sha, t_scene *sc, t_vec3 *total, t_emissive_ref ref);
void	em_rect(t_shading *sha, t_scene *sc, t_vec3 *total, t_emissive_ref ref);

void	em_surf(t_shading *sha, t_scene *sc, t_vec3 *total,
				t_emissive_ref ref)
{
	if (ref.type == TYPE_TRI)
		em_tri(sha, sc, total, ref);
	else if (ref.type == TYPE_RECT)
		em_rect(sha, sc, total, ref);
	else if (ref.type == TYPE_PYRAMID)
	{
		sha->aux_v = vec3_sub(sc->pyramids[ref.index].transform.pos,
				sha->hit->point);
		sha->em_normal = vec3(0, 0, 0);
		apply_em(sha, total, &sc->materials[sc->pyramids[ref.index].mat_id],
			sc->pyramids[ref.index].base_size * 0.5);
	}
}
