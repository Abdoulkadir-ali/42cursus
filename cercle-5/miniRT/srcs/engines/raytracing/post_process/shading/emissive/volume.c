/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   volume.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 11:37:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/07 22:36:07 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

static void	em_cap(t_shading *sha, t_scene *sc, t_vec3 *total,
				t_emissive_ref ref)
{
	t_capsule	*cp;
	t_material	*mat;

	cp = &sc->capsules[ref.index];
	mat = &sc->materials[cp->mat_id];
	sha->aux_v = vec3_sub(cp->transform.pos, sha->hit->point);
	sha->em_normal = vec3(0, 0, 0);
	apply_em(sha, total, mat, cp->radius + cp->half_height);
	sha->aux_v = vec3_sub(vec3_sub(cp->transform.pos,
				vec3_scale(cp->axis, cp->half_height)), sha->hit->point);
	sha->em_normal = vec3_scale(cp->axis, -1.0);
	apply_em(sha, total, mat, cp->radius);
	sha->aux_v = vec3_sub(vec3_add(cp->transform.pos,
				vec3_scale(cp->axis, cp->half_height)), sha->hit->point);
	sha->em_normal = cp->axis;
	apply_em(sha, total, mat, cp->radius);
}

static void	em_cylinder_sub(t_shading *sha, t_scene *sc, t_vec3 *total,
				t_emissive_ref ref)
{
	t_cylinder	*cy;
	t_material	*mat;
	double		r;
	t_vec3		mid;

	cy = &sc->cylinders[ref.index];
	mat = &sc->materials[cy->mat_id];
	r = cy->transform.scale.x;
	mid = vec3_add(cy->transform.pos,
			vec3_scale(cy->transform.forward, cy->transform.scale.y * 0.5));
	sha->aux_v = vec3_sub(mid, sha->hit->point);
	sha->em_normal = vec3(0, 0, 0);
	apply_em(sha, total, mat, r);
	sha->aux_v = vec3_sub(cy->transform.pos, sha->hit->point);
	sha->em_normal = vec3_scale(cy->transform.forward, -1.0);
	apply_em(sha, total, mat, r);
	sha->aux_v = vec3_sub(cy->top, sha->hit->point);
	sha->em_normal = cy->transform.forward;
	apply_em(sha, total, mat, r);
}

static void	em_cone_sub(t_shading *sha, t_scene *sc, t_vec3 *total,
				t_emissive_ref ref)
{
	t_cone		*cn;
	t_material	*mat;
	double		r;
	t_vec3		base;
	t_vec3		mid;

	cn = &sc->cones[ref.index];
	mat = &sc->materials[cn->mat_id];
	r = cn->transform.scale.x;
	mid = vec3_add(cn->transform.pos,
			vec3_scale(cn->transform.forward, cn->transform.scale.y * 0.5));
	base = vec3_add(cn->transform.pos,
			vec3_scale(cn->transform.forward, cn->transform.scale.y));
	sha->aux_v = vec3_sub(mid, sha->hit->point);
	sha->em_normal = vec3(0, 0, 0);
	apply_em(sha, total, mat, r * 0.5);
	sha->aux_v = vec3_sub(base, sha->hit->point);
	sha->em_normal = cn->transform.forward;
	apply_em(sha, total, mat, r);
}

static bool	em_vol_sub(t_shading *sha, t_scene *sc, t_vec3 *total,
				t_emissive_ref ref)
{
	t_sphere	*sp;
	t_box		*bx;

	if (ref.type == TYPE_SPHERE)
	{
		sp = &sc->spheres[ref.index];
		sha->aux_v = vec3_sub(sp->transform.pos, sha->hit->point);
		sha->em_normal = vec3(0, 0, 0);
		apply_em(sha, total, &sc->materials[sp->mat_id],
			fmax(fabs(sp->transform.scale.x), 1.0) * sqrt(sp->radius_sq));
		return (true);
	}
	if (ref.type == TYPE_BOX)
	{
		bx = &sc->boxes[ref.index];
		sha->aux_v = vec3_sub(bx->transform.pos, sha->hit->point);
		sha->em_normal = vec3(0, 0, 0);
		apply_em(sha, total, &sc->materials[bx->mat_id],
			fmax(fmax(bx->half_extents.x, bx->half_extents.y),
				bx->half_extents.z));
		return (true);
	}
	return (false);
}

void	em_vol(t_shading *sha, t_scene *sc, t_vec3 *total,
				t_emissive_ref ref)
{
	if (em_vol_sub(sha, sc, total, ref))
		return ;
	if (ref.type == TYPE_CAPSULE)
		em_cap(sha, sc, total, ref);
	else if (ref.type == TYPE_CYLINDER)
		em_cylinder_sub(sha, sc, total, ref);
	else if (ref.type == TYPE_CONE)
		em_cone_sub(sha, sc, total, ref);
}
