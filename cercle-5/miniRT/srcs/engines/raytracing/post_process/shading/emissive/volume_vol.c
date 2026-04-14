/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   volume_vol.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 11:37:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/12 22:03:20 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

static void	em_sphere(t_shading *sha, t_scene *sc, t_vec3 *total,
			t_emissive_ref ref)
{
	t_sphere	*sp;
	t_vec3		d;
	t_vec3		cl;
	double		r;
	double		m;

	sp = &sc->spheres[ref.index];
	r = fmax(fabs(sp->transform.scale.x), 1.0) * sqrt(sp->radius_sq);
	d = vec3_sub(sha->hit->point, sp->transform.pos);
	if (vec3_mag_sq(d) > ref.reach_center_sq)
		return ;
	m = vec3_mag(d);
	cl = vec3_add(sp->transform.pos, vec3(r, 0, 0));
	if (m >= 1e-9)
		cl = vec3_add(sp->transform.pos, vec3_scale(d, r / m));
	sha->aux_v = vec3_sub(cl, sha->hit->point);
	sha->em_normal = vec3(0, 0, 0);
	apply_em(sha, total, &sc->materials[sp->mat_id], r);
}

static t_vec3	clamp_box_pt(t_vec3 d, t_box *bx)
{
	t_vec3	ox;
	t_vec3	oy;
	t_vec3	oz;

	ox = vec3_scale(bx->transform.right, fmax(-bx->half_extents.x,
				fmin(bx->half_extents.x, vec3_dot(d, bx->transform.right))));
	oy = vec3_scale(bx->transform.up, fmax(-bx->half_extents.y,
				fmin(bx->half_extents.y, vec3_dot(d, bx->transform.up))));
	oz = vec3_scale(bx->transform.forward, fmax(-bx->half_extents.z,
				fmin(bx->half_extents.z, vec3_dot(d, bx->transform.forward))));
	return (vec3_add(ox, vec3_add(oy, oz)));
}

static void	em_box(t_shading *sha, t_scene *sc, t_vec3 *total,
			t_emissive_ref ref)
{
	t_box	*bx;
	t_vec3	d;
	double	r;

	bx = &sc->boxes[ref.index];
	d = vec3_sub(sha->hit->point, bx->transform.pos);
	sha->aux_v = vec3_sub(vec3_add(bx->transform.pos,
				clamp_box_pt(d, bx)), sha->hit->point);
	sha->em_normal = vec3(0, 0, 0);
	r = fmax(fmax(bx->half_extents.x, bx->half_extents.y),
			bx->half_extents.z);
	apply_em(sha, total, &sc->materials[bx->mat_id], r);
}

void	em_vol(t_shading *sha, t_scene *sc, t_vec3 *total,
			t_emissive_ref ref)
{
	if (ref.type == TYPE_SPHERE)
		em_sphere(sha, sc, total, ref);
	else if (ref.type == TYPE_BOX)
		em_box(sha, sc, total, ref);
	else if (ref.type == TYPE_CAPSULE)
		em_cap(sha, sc, total, ref);
	else if (ref.type == TYPE_CYLINDER)
		em_cylinder_sub(sha, sc, total, ref);
	else if (ref.type == TYPE_CONE)
		em_cone_sub(sha, sc, total, ref);
}
