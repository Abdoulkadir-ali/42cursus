/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   volume.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 11:37:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/09 23:57:57 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

/*
** closest_pt_seg: closest point on segment [a, b] to point p.
*/
static t_vec3	closest_pt_seg(t_vec3 p, t_vec3 a, t_vec3 b)
{
	t_vec3	ab;
	t_vec3	ap;
	double	t;
	double	len2;

	ab = vec3_sub(b, a);
	ap = vec3_sub(p, a);
	len2 = vec3_dot(ab, ab);
	if (len2 < 1e-12)
		return (a);
	t = fmax(0.0, fmin(1.0, vec3_dot(ap, ab) / len2));
	return (vec3_add(a, vec3_scale(ab, t)));
}

/*
** closest_surf_cyl: closest point on the curved wall of a finite cylinder.
** base = transform.pos, top = precomputed top endpoint, r = radius.
** The returned point lies on the cylindrical surface (at distance r from axis).
*/
static t_vec3	closest_surf_cyl(t_vec3 p, t_vec3 base, t_vec3 top,
					t_vec3 axis, double r, t_vec3 fallback_tan)
{
	t_vec3	axis_pt;
	t_vec3	radial;
	double	rd;

	axis_pt = closest_pt_seg(p, base, top);
	radial = vec3_sub(p, axis_pt);
	radial = vec3_sub(radial,
			vec3_scale(axis, vec3_dot(radial, axis)));
	rd = vec3_mag(radial);
	if (rd < 1e-9)
		return (vec3_add(axis_pt, vec3_scale(fallback_tan, r)));
	return (vec3_add(axis_pt, vec3_scale(radial, r / rd)));
}

static void	em_cap(t_shading *sha, t_scene *sc, t_vec3 *total,
				t_emissive_ref ref)
{
	t_capsule	*cp;
	t_material	*mat;
	t_vec3		a;
	t_vec3		b;
	t_vec3		seg_pt;
	t_vec3		radial;
	double		rd;
	t_vec3		closest;

	cp = &sc->capsules[ref.index];
	mat = &sc->materials[cp->mat_id];
	a = vec3_sub(cp->transform.pos, vec3_scale(cp->axis, cp->half_height));
	b = vec3_add(cp->transform.pos, vec3_scale(cp->axis, cp->half_height));
	seg_pt = closest_pt_seg(sha->hit->point, a, b);
	radial = vec3_sub(sha->hit->point, seg_pt);
	rd = vec3_mag(radial);
	if (rd < 1e-9)
		closest = vec3_add(seg_pt, vec3_scale(vec3(1, 0, 0), cp->radius));
	else
		closest = vec3_add(seg_pt, vec3_scale(radial, cp->radius / rd));
	sha->em_normal = vec3(0, 0, 0);
	sha->aux_v = vec3_sub(closest, sha->hit->point);
	apply_em(sha, total, mat, cp->radius + cp->half_height);
}

static void	em_cylinder_sub(t_shading *sha, t_scene *sc, t_vec3 *total,
				t_emissive_ref ref)
{
	t_cylinder	*cy;
	t_material	*mat;
	double		r;
	t_vec3		closest;

	cy = &sc->cylinders[ref.index];
	mat = &sc->materials[cy->mat_id];
	r = cy->transform.scale.x;
	closest = closest_surf_cyl(sha->hit->point, cy->transform.pos, cy->top,
			cy->transform.forward, r, cy->local_u);
	sha->aux_v = vec3_sub(closest, sha->hit->point);
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
	t_vec3		closest;

	cn = &sc->cones[ref.index];
	mat = &sc->materials[cn->mat_id];
	r = cn->transform.scale.x;
	base = vec3_add(cn->transform.pos,
			vec3_scale(cn->transform.forward, cn->transform.scale.y));
	closest = closest_surf_cyl(sha->hit->point, cn->transform.pos, base,
			cn->transform.forward, r * 0.5, cn->transform.right);
	sha->aux_v = vec3_sub(closest, sha->hit->point);
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
	t_vec3		d;
	t_vec3		closest;
	double		r;

	if (ref.type == TYPE_SPHERE)
	{
		sp = &sc->spheres[ref.index];
		r = fmax(fabs(sp->transform.scale.x), 1.0) * sqrt(sp->radius_sq);
		d = vec3_sub(sha->hit->point, sp->transform.pos);
		closest = (vec3_mag(d) < 1e-9)
			? vec3_add(sp->transform.pos, vec3(r, 0, 0))
			: vec3_add(sp->transform.pos, vec3_scale(d, r / vec3_mag(d)));
		sha->aux_v = vec3_sub(closest, sha->hit->point);
		sha->em_normal = vec3(0, 0, 0);
		apply_em(sha, total, &sc->materials[sp->mat_id], r);
		return (true);
	}
	if (ref.type == TYPE_BOX)
	{
		bx = &sc->boxes[ref.index];
		d = vec3_sub(sha->hit->point, bx->transform.pos);
		closest = vec3_add(bx->transform.pos,
				vec3_add(vec3_add(
						vec3_scale(bx->transform.right,
							fmax(-bx->half_extents.x, fmin(bx->half_extents.x,
								vec3_dot(d, bx->transform.right)))),
						vec3_scale(bx->transform.up,
							fmax(-bx->half_extents.y, fmin(bx->half_extents.y,
								vec3_dot(d, bx->transform.up))))),
					vec3_scale(bx->transform.forward,
						fmax(-bx->half_extents.z, fmin(bx->half_extents.z,
							vec3_dot(d, bx->transform.forward))))));
		sha->em_normal = vec3(0, 0, 0);
		sha->aux_v = vec3_sub(closest, sha->hit->point);
		r = fmax(fmax(bx->half_extents.x, bx->half_extents.y),
				bx->half_extents.z);
		apply_em(sha, total, &sc->materials[bx->mat_id], r);
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
