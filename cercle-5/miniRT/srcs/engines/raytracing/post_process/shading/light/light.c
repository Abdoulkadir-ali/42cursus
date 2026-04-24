/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/24 20:32:37 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

double	shading_attenuation(double dist_sq)
{
	return (1.0 / (1.0 + 0.05 * dist_sq));
}

__attribute__((optimize("O3")))
bool	light_visible(t_shading *sha, t_light light, t_light_calc *c)
{
	if (light.type == LIGHT_SPOT && vec3_dot(vec3_scale(c->norm, -1.0),
			light.transform.forward) < light.cutoff)
		return (false);
	if (light.type == LIGHT_EMISSIVE)
		return (true);
	if (is_in_shadow(sha->bvh, sha->cache.org, c->norm, c->dist - 1e-3))
		return (false);
	return (true);
}

static inline float	fast_powf(float base, float exp)
{
	return (exp2f(exp * log2f(base)));
}

__attribute__((optimize("O3")))
double	calc_specular(t_shading *sha, t_vec3 ld_norm)
{
	t_vec3	half;
	float	ndoth;

	half = vec3_norm(vec3_add(ld_norm, sha->cache.view));
	ndoth = (float)vec3_dot(sha->hit->normal, half);
	if (ndoth < 0.0f)
		ndoth = 0.0f;
	if (ndoth < 0.01f)
		return (0.0);
	if (sha->opts && sha->opts->blinn_phong)
		return ((double)fast_powf(ndoth, (float)sha->mat.shininess));
	return ((double)(ndoth / (sha->mat.shininess
			- sha->mat.shininess * ndoth + ndoth)));
}
