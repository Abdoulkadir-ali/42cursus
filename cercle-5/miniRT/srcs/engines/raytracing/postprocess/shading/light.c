/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/13 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

/*
** Inverse-square attenuation with adjustable constant to avoid
** blow-out at close range.  att = 1 / (1 + k * d^2)
*/
static double	light_attenuation(double dist_sq)
{
	return (1.0 / (1.0 + 0.05 * dist_sq));
}

static bool	light_visible(t_shading *sha, t_light light, t_vec3 ld_norm,
		double dist, double ndotl)
{
	double	bias;

	if (light.type == LIGHT_SPOT && vec3_dot(vec3_scale(ld_norm, -1.0),
			light.transform.forward) < light.cutoff)
		return (false);
	if (light.type == LIGHT_EMISSIVE)
		return (true);
	bias = fmax(EPSILON, EPSILON * 20.0 * (1.0 - ndotl));
	if (is_in_shadow(sha->bvh, vec3_add(sha->hit->point,
				vec3_scale(sha->hit->normal, bias)), ld_norm, dist))
		return (false);
	return (true);
}

/*
** Calculates lighting contribution for a single light source.
** Includes inverse-square distance attenuation.
*/
/*
** Calculates lighting contribution for a single light source.
** Standard directional/point lights are unattenuated (matches legacy miniRT).
*/
t_vec3	calc_light(t_shading *sha, t_light light)
{
	t_vec3	ld;
	t_vec3	ld_norm;
	double	dist;
	double	ndotl;
	t_vec3	half;
	double	spec;

	ld = vec3_sub(light.transform.pos, sha->hit->point);
	dist = vec3_mag(ld);
	if (dist < 1e-8)
		return (vec3(0, 0, 0));
	ld_norm = vec3_scale(ld, 1.0 / dist);
	ndotl = vec3_dot(sha->hit->normal, ld_norm);
	if (ndotl < 0.02)
		return (vec3(0, 0, 0));
	if (!light_visible(sha, light, ld_norm, dist, ndotl))
		return (vec3(0, 0, 0));
	half = vec3_norm(vec3_add(ld_norm,
				vec3_scale(sha->ray->direction, -1.0)));
	{
		float	ndoth;
		ndoth = (float)fmax(0.0, vec3_dot(sha->hit->normal, half));
		if (ndoth < 0.01f)
			spec = 0.0;
		else
			spec = (double)powf(ndoth, (float)sha->mat.shininess);
	}
	return (vec3_add(pixel_color(sha->albedo, light.rgb, light.brightness
				* ndotl), vec3_scale(light.rgb, light.brightness
				* sha->mat.specular * spec)));
}

static void	apply_emissive(t_shading *sha, t_vec3 *total,
		t_material *mat, t_vec3 ld_rad)
{
	double	dist_surf;
	t_vec3	ldir;
	double	ndotl;
	double	att;
	double	bright;

	if (vec3_mag_sq(sha->aux_v) > 2500.0)
		return ;
	dist_surf = vec3_mag(sha->aux_v) - ld_rad.x - 0.01;
	if (dist_surf <= 0.0)
		return ;
	ldir = vec3_norm(sha->aux_v);
	ndotl = vec3_dot(sha->hit->normal, ldir);
	if (ndotl < 0.02)
		return ;
	if (is_in_shadow(sha->bvh, vec3_add(sha->hit->point, vec3_scale(
					sha->hit->normal, fmax(EPSILON, EPSILON * 20.0 * (1.0 - ndotl)))),
			ldir, dist_surf))
		return ;
	att = light_attenuation(dist_surf * dist_surf);
	bright = vec3_mag(mat->emission) / 255.0 * fmax(ld_rad.x, 0.5) * 3.0;
	{
		float	ndoth;
		double	spec_e;
		ndoth = (float)fmax(0.0, vec3_dot(sha->hit->normal,
					vec3_norm(vec3_add(ldir,
							vec3_scale(sha->ray->direction, -1.0)))));
		if (ndoth < 0.01f)
			spec_e = 0.0;
		else
			spec_e = (double)powf(ndoth, (float)sha->mat.shininess);
		*total = vec3_add(*total, vec3_add(pixel_color(sha->albedo,
						mat->emission, bright * ndotl * att),
					vec3_scale(mat->emission,
						bright * sha->mat.specular * att * spec_e)));
	}
}

static void	emissive_from_ref(t_shading *sha, t_scene *sc, t_vec3 *total,
		t_emissive_ref ref)
{
	t_sphere	*sp;
	t_tri_shape	*tr;
	t_rect		*rc;
	t_pyramid	*py;
	t_box		*bx;
	t_capsule	*cap;
	t_mesh		*m;
	t_vec3		c;
	double		r;

	if (ref.type == TYPE_SPHERE)
	{
		sp = &sc->spheres[ref.index];
		r = fmax(fabs(sp->transform.scale.x), 1.0) * sqrt(sp->radius_sq);
		sha->aux_v = vec3_sub(sp->transform.pos, sha->hit->point);
		apply_emissive(sha, total, &sc->materials[sp->mat_id], vec3(r, 0, 0));
	}
	else if (ref.type == TYPE_TRI)
	{
		tr = &sc->tris[ref.index];
		c = vec3_scale(vec3_add(vec3_add(tr->v[0], tr->v[1]), tr->v[2]),
				1.0 / 3.0);
		sha->aux_v = vec3_sub(c, sha->hit->point);
		apply_emissive(sha, total, &sc->materials[tr->mat_id], vec3(0.5, 0, 0));
	}
	else if (ref.type == TYPE_RECT)
	{
		rc = &sc->rects[ref.index];
		sha->aux_v = vec3_sub(rc->transform.pos, sha->hit->point);
		apply_emissive(sha, total, &sc->materials[rc->mat_id], vec3(0.7, 0, 0));
	}
	else if (ref.type == TYPE_PYRAMID)
	{
		py = &sc->pyramids[ref.index];
		sha->aux_v = vec3_sub(py->transform.pos, sha->hit->point);
		apply_emissive(sha, total, &sc->materials[py->mat_id],
			vec3(py->base_size * 0.5, 0, 0));
	}
	else if (ref.type == TYPE_BOX)
	{
		bx = &sc->boxes[ref.index];
		r = fmax(fmax(bx->half_extents.x, bx->half_extents.y),
				bx->half_extents.z);
		sha->aux_v = vec3_sub(bx->transform.pos, sha->hit->point);
		apply_emissive(sha, total, &sc->materials[bx->mat_id], vec3(r, 0, 0));
	}
	else if (ref.type == TYPE_CAPSULE)
	{
		cap = &sc->capsules[ref.index];
		sha->aux_v = vec3_sub(cap->transform.pos, sha->hit->point);
		apply_emissive(sha, total, &sc->materials[cap->mat_id],
			vec3(cap->radius + cap->half_height, 0, 0));
	}
	else if (ref.type == TYPE_MESH)
	{
		m = &sc->meshes[ref.index];
		c = vec3_add(m->transform.pos,
				vec3_scale(vec3_add(m->bbox.min, m->bbox.max), 0.5));
		sha->aux_v = vec3_sub(c, sha->hit->point);
		apply_emissive(sha, total, &sc->materials[m->mat_id],
			vec3(vec3_mag(vec3_scale(
						vec3_sub(m->bbox.max, m->bbox.min), 0.5)), 0, 0));
	}
}

/*
** Iterate only the pre-built emissive cache (O(E) not O(N)).
*/
void	add_emissive_lighting(t_shading *sha, t_scene *sc, t_vec3 *total)
{
	int	i;

	i = -1;
	while (++i < sc->emissive_n)
		emissive_from_ref(sha, sc, total, sc->emissive_cache[i]);
}
