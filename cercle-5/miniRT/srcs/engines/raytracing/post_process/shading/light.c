/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/10 00:30:12 by abdoali          ###   ########.fr       */
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

static double	calc_specular(t_shading *sha, t_vec3 ld_norm)
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

/*
** Calculates lighting contribution for a single light source.
*/
t_vec3	calc_light(t_shading *sha, t_light light)
{
	t_light_calc	c;
	double			spec;
	t_vec3			diff;
	t_vec3			target;
	uint32_t		seed;
	double			radius;
	double			area_norm;

	radius = light.transform.scale.x;
	target = light.transform.pos;
	c.target = target;
	area_norm = 1.0;
	if (radius > 1e-4)
	{
		t_vec3	to_light = vec3_sub(light.transform.pos, sha->hit->point);
		double	dist = vec3_mag(to_light);
		if (radius < dist)
		{
			double cos_theta_max = sqrt(fmax(0.0, 1.0 - (radius * radius) / (dist * dist)));
			seed = (uint32_t)sha->frame_idx * 1664525 + (uint32_t)light.id;
			seed ^= (uint32_t)(sha->hit->point.x * 1000.0) ^ (uint32_t)(sha->hit->point.z * 1000.0);
			c.norm = rt_random_on_cone(vec3_norm(to_light), cos_theta_max, &seed);
			double b_val = 2.0 * vec3_dot(c.norm, vec3_scale(to_light, -1.0));
			double c_val = dist * dist - radius * radius;
			double det = b_val * b_val - 4.0 * c_val;
			c.dist = (double)fmax(0.0, (-b_val - sqrt(fmax(0.0, det))) * 0.5);
			target = vec3_add(sha->hit->point, vec3_scale(c.norm, c.dist));
			c.target = target;
			area_norm = 4.0 * PI * radius * radius;
		}
	}
	c.ld = vec3_sub(target, sha->hit->point);
	c.dist = vec3_mag(c.ld);
	if (c.dist < 1e-8)
		return (vec3(0, 0, 0));
	c.norm = vec3_scale(c.ld, 1.0 / c.dist);
	c.ndotl = vec3_dot(sha->hit->normal, c.norm);
	if (c.ndotl < 0.0)
		return (vec3(0, 0, 0));
	double b = light.brightness / area_norm;
	double att = 1.0 / (c.dist * c.dist + 1.0);
	if (!sha->opts || sha->opts->beer_enabled)
	{
		double density = (sha->opts && sha->opts->beer_density > 0.0)
			? sha->opts->beer_density : 0.02;
		att *= exp(-density * c.dist);
	}
	if (b * att * c.ndotl < 0.004)
		return (vec3(0, 0, 0));
	if (!light_visible(sha, light, &c))
		return (vec3(0, 0, 0));
	spec = calc_specular(sha, c.norm);
	diff = pixel_color(sha->albedo, light.rgb, fmin(b * att, 200.0) * c.ndotl);
	return (vec3_add(diff, vec3_scale(light.rgb, fmin(b * att, 200.0)
				* sha->mat.specular * spec)));
}
