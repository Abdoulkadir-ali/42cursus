/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   emissive.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 11:37:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 23:51:35 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

static void	apply_em_val(t_shading *sha, t_vec3 *total,
				t_material *mat, double r)
{
	double	d_surf;
	t_vec3	ldir;
	double	ndotl;
	double	bright;
	double	att;

	if (vec3_mag_sq(sha->aux_v) > 2500.0)
		return ;
	d_surf = vec3_mag(sha->aux_v) - r - 0.01;
	if (d_surf <= 0.0)
		return ;
	ldir = vec3_norm(sha->aux_v);
	ndotl = vec3_dot(sha->hit->normal, ldir);
	if (ndotl < 0.02)
		return ;
	if (is_in_shadow(sha->bvh, sha->hit->point, ldir, d_surf,
					sha->hit->ref))
		return ;
	bright = vec3_mag(mat->emission) / 255.0 * fmax(r, 0.5) * 3.0;
	att = shading_attenuation(d_surf * d_surf);
	*total = vec3_add(*total, pixel_color(sha->albedo, mat->emission,
				bright * ndotl * att));
	sha->aux_v = vec3_scale(ldir, bright * sha->mat.specular * att);
}

void	apply_em(t_shading *sha, t_vec3 *total, t_material *mat, double r)
{
	double	spec;
	t_vec3	ldir;
	double	spec_val;

	ldir = vec3_norm(sha->aux_v);
	spec_val = vec3_mag(sha->aux_v);
	apply_em_val(sha, total, mat, r);
	spec = (double) powf((float) fmax(0.0, vec3_dot(sha->hit->normal,
					vec3_norm(vec3_add(ldir,
							vec3_scale(sha->ray->direction, -1.0))))),
			(float) sha->mat.shininess);
	*total = vec3_add(*total, vec3_scale(mat->emission,
				spec_val * spec));
}

void	add_emissive_lighting(t_shading *sha, t_scene *sc, t_vec3 *total)
{
	size_t			i;
	t_emissive_ref	ref;
	t_mesh			*m;

	i = 0;
	while (i < sc->emissive_n)
	{
		ref = sc->emissive_cache[i++];
		em_vol(sha, sc, total, ref);
		em_surf(sha, sc, total, ref);
		if (ref.type == TYPE_MESH)
		{
			m = &sc->meshes[ref.index];
			sha->aux_v = vec3_sub(vec3_add(m->transform.pos, vec3_scale(
							vec3_add(m->bbox.min, m->bbox.max), 0.5)),
					sha->hit->point);
			apply_em(sha, total, &sc->materials[m->mat_id], vec3_mag(
					vec3_scale(vec3_sub(m->bbox.max, m->bbox.min), 0.5)));
		}
	}
}
