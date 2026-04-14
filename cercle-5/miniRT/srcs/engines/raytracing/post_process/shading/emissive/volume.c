/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   volume.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 11:37:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/12 21:50:51 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

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

static t_vec3	closest_surf_cyl(t_vec3 p, t_cyl_info info)
{
	t_vec3	axis_pt;
	t_vec3	radial;
	double	rd;

	axis_pt = closest_pt_seg(p, info.base, info.top);
	radial = vec3_sub(p, axis_pt);
	radial = vec3_sub(radial,
			vec3_scale(info.axis, vec3_dot(radial, info.axis)));
	rd = vec3_mag(radial);
	if (rd < 1e-9)
		return (vec3_add(axis_pt, vec3_scale(info.tan, info.r)));
	return (vec3_add(axis_pt, vec3_scale(radial, info.r / rd)));
}

void	em_cap(t_shading *sha, t_scene *sc, t_vec3 *total,
			t_emissive_ref ref)
{
	t_capsule	*cp;
	t_vec3		a;
	t_vec3		b;
	t_vec3		seg_pt;
	t_vec3		radial;

	cp = &sc->capsules[ref.index];
	a = vec3_sub(cp->transform.pos,
			vec3_scale(cp->axis, cp->half_height));
	b = vec3_add(cp->transform.pos,
			vec3_scale(cp->axis, cp->half_height));
	seg_pt = closest_pt_seg(sha->hit->point, a, b);
	radial = vec3_sub(sha->hit->point, seg_pt);
	sha->aux_v = vec3_add(seg_pt,
			vec3_scale(vec3(1, 0, 0), cp->radius));
	if (vec3_mag(radial) >= 1e-9)
		sha->aux_v = vec3_add(seg_pt,
				vec3_scale(radial, cp->radius / vec3_mag(radial)));
	sha->aux_v = vec3_sub(sha->aux_v, sha->hit->point);
	sha->em_normal = vec3(0, 0, 0);
	apply_em(sha, total, &sc->materials[cp->mat_id],
		cp->radius + cp->half_height);
}

void	em_cylinder_sub(t_shading *sha, t_scene *sc, t_vec3 *total,
			t_emissive_ref ref)
{
	t_cylinder	*cy;
	t_cyl_info	info;
	t_vec3		closest;

	cy = &sc->cylinders[ref.index];
	info.base = cy->transform.pos;
	info.top = cy->top;
	info.axis = cy->transform.forward;
	info.r = cy->transform.scale.x;
	info.tan = cy->local_u;
	closest = closest_surf_cyl(sha->hit->point, info);
	sha->aux_v = vec3_sub(closest, sha->hit->point);
	sha->em_normal = vec3(0, 0, 0);
	apply_em(sha, total, &sc->materials[cy->mat_id], info.r);
	sha->aux_v = vec3_sub(cy->transform.pos, sha->hit->point);
	sha->em_normal = vec3_scale(cy->transform.forward, -1.0);
	apply_em(sha, total, &sc->materials[cy->mat_id], info.r);
	sha->aux_v = vec3_sub(cy->top, sha->hit->point);
	sha->em_normal = cy->transform.forward;
	apply_em(sha, total, &sc->materials[cy->mat_id], info.r);
}

void	em_cone_sub(t_shading *sha, t_scene *sc, t_vec3 *total,
			t_emissive_ref ref)
{
	t_cone		*cn;
	t_cyl_info	info;
	t_vec3		base;

	cn = &sc->cones[ref.index];
	info.r = cn->transform.scale.x;
	base = vec3_add(cn->transform.pos,
			vec3_scale(cn->transform.forward, cn->transform.scale.y));
	info.base = cn->transform.pos;
	info.top = base;
	info.axis = cn->transform.forward;
	info.tan = cn->transform.right;
	sha->aux_v = vec3_sub(closest_surf_cyl(sha->hit->point, info),
			sha->hit->point);
	sha->em_normal = vec3(0, 0, 0);
	apply_em(sha, total, &sc->materials[cn->mat_id], info.r * 0.5);
	sha->aux_v = vec3_sub(base, sha->hit->point);
	sha->em_normal = cn->transform.forward;
	apply_em(sha, total, &sc->materials[cn->mat_id], info.r);
}
