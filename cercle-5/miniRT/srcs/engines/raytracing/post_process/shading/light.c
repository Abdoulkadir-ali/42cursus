/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 11:32:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

/*
** att = 1 / (1 + k * d^2) - not used for direct light default but kept here.
*/
double	shading_attenuation(double dist_sq)
{
	return (1.0 / (1.0 + 0.05 * dist_sq));
}

static bool	light_visible(t_shading *sha, t_light light, t_light_calc *c)
{
	double	bias;

	if (light.type == LIGHT_SPOT && vec3_dot(vec3_scale(c->norm, -1.0),
			light.transform.forward) < light.cutoff)
		return (false);
	if (light.type == LIGHT_EMISSIVE)
		return (true);
	bias = fmax(EPSILON, EPSILON * 20.0 * (1.0 - c->ndotl));
	if (is_in_shadow(sha->bvh, vec3_add(sha->hit->point,
				vec3_scale(sha->hit->normal, bias)), c->norm, c->dist))
		return (false);
	return (true);
}

static double	calc_specular(t_shading *sha, t_vec3 ld_norm)
{
	t_vec3	half;
	float	ndoth;

	half = vec3_norm(vec3_add(ld_norm, vec3_scale(sha->ray->direction, -1.0)));
	ndoth = (float)fmax(0.0, vec3_dot(sha->hit->normal, half));
	if (ndoth < 0.01f)
		return (0.0);
	return ((double)powf(ndoth, (float)sha->mat.shininess));
}

/*
** Calculates lighting contribution for a single light source.
*/
t_vec3	calc_light(t_shading *sha, t_light light)
{
	t_light_calc	c;
	double			spec;
	t_vec3			diff;

	c.ld = vec3_sub(light.transform.pos, sha->hit->point);
	c.dist = vec3_mag(c.ld);
	if (c.dist < 1e-8)
		return (vec3(0, 0, 0));
	c.norm = vec3_scale(c.ld, 1.0 / c.dist);
	c.ndotl = vec3_dot(sha->hit->normal, c.norm);
	if (c.ndotl < 0.02)
		return (vec3(0, 0, 0));
	if (!light_visible(sha, light, &c))
		return (vec3(0, 0, 0));
	spec = calc_specular(sha, c.norm);
	diff = pixel_color(sha->albedo, light.rgb, light.brightness * c.ndotl);
	return (vec3_add(diff, vec3_scale(light.rgb, light.brightness
				* sha->mat.specular * spec)));
}
