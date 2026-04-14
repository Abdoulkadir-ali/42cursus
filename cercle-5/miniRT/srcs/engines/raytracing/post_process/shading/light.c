/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/14 10:13:32 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

double	shading_attenuation(double dist_sq)
{
	return (1.0 / (1.0 + 0.05 * dist_sq));
}

bool	light_visible(t_shading *sha, t_light light, t_light_calc *c)
{
	t_vec3	org;
	t_vec3	dir;
	double	dist;

	if (light.type == LIGHT_SPOT && vec3_dot(vec3_scale(c->norm, -1.0),
			light.transform.forward) < light.cutoff)
		return (false);
	if (light.type == LIGHT_EMISSIVE)
		return (true);
	org = vec3_add(sha->hit->point, vec3_scale(sha->hit->normal, 1e-3));
	dir = vec3_sub(c->target, org);
	dist = vec3_mag(dir);
	if (is_in_shadow(sha->bvh, org, vec3_scale(dir, 1.0 / dist), dist - 1e-3))
		return (false);
	return (true);
}

double	calc_specular(t_shading *sha, t_vec3 ld_norm)
{
	t_vec3	half;
	float	ndoth;

	half = vec3_norm(vec3_add(ld_norm, vec3_scale(sha->ray->direction, -1.0)));
	ndoth = (float)fmax(0.0, vec3_dot(sha->hit->normal, half));
	if (ndoth < 0.01f)
		return (0.0);
	if (sha->opts && sha->opts->blinn_phong)
		return ((double)powf(ndoth, (float)sha->mat.shininess));
	return ((double)(ndoth / (sha->mat.shininess
			- sha->mat.shininess * ndoth + ndoth)));
}
