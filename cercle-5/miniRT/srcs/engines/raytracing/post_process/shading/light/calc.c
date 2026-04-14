/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_calc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/10 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

static void	stochastic_target(t_shading *sha, t_light light, t_light_calc *c,
				double *a_norm)
{
	t_vec3		to_light;
	double		dist;
	double		cos_theta_max;
	uint32_t	seed;
	double		bv;

	to_light = vec3_sub(light.transform.pos, sha->hit->point);
	dist = vec3_mag(to_light);
	if (light.transform.scale.x >= dist)
		return ;
	bv = light.transform.scale.x / dist;
	cos_theta_max = sqrt(fmax(0.0, 1.0 - bv * bv));
	seed = (uint32_t)sha->frame_idx * 1664525 + (uint32_t)light.id;
	seed ^= (uint32_t)(sha->hit->point.x * 1000.0)
		^ (uint32_t)(sha->hit->point.z * 1000.0);
	c->norm = rt_random_on_cone(vec3_norm(to_light), cos_theta_max, &seed);
	bv = 2.0 * vec3_dot(c->norm, vec3_scale(to_light, -1.0));
	dist = dist * dist - light.transform.scale.x * light.transform.scale.x;
	cos_theta_max = sqrt(fmax(0.0, bv * bv - 4.0 * dist));
	dist = (double)fmax(0.0, (-bv - cos_theta_max) * 0.5);
	c->target = vec3_add(sha->hit->point, vec3_scale(c->norm, dist));
	*a_norm = 4.0 * PI * light.transform.scale.x * light.transform.scale.x;
}

static double	get_attenuation(t_shading *sha, t_light_calc *c)
{
	double	att;
	double	density;

	att = 1.0 / (c->dist * c->dist + 1.0);
	if (!sha->opts || sha->opts->beer_enabled)
	{
		density = 0.02;
		if (sha->opts && sha->opts->beer_density > 0.0)
			density = sha->opts->beer_density;
		att *= exp(-density * c->dist);
	}
	return (att);
}

t_vec3	calc_light(t_shading *sha, t_light light)
{
	t_light_calc	c;
	double			spec;
	double			b;
	double			att;

	c.target = light.transform.pos;
	b = 1.0;
	if (light.transform.scale.x > 1e-4 && (!sha->opts
			|| sha->opts->stochastic_lights))
		stochastic_target(sha, light, &c, &b);
	c.ld = vec3_sub(c.target, sha->hit->point);
	c.dist = vec3_mag(c.ld);
	if (c.dist < 1e-8)
		return (vec3(0, 0, 0));
	c.norm = vec3_scale(c.ld, 1.0 / c.dist);
	c.ndotl = vec3_dot(sha->hit->normal, c.norm);
	att = get_attenuation(sha, &c);
	b = light.brightness / b;
	if (c.ndotl < 0.0 || b * att * c.ndotl < 0.004
		|| !light_visible(sha, light, &c))
		return (vec3(0, 0, 0));
	spec = calc_specular(sha, c.norm);
	b = fmin(b * att, 200.0) * c.ndotl;
	return (vec3_add(pixel_color(sha->albedo, light.rgb, b),
			vec3_scale(light.rgb, b * sha->mat.specular * spec)));
}
