/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 10:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

static bool	light_visible(t_shading *sha, const t_rt_engine *rt, 
		t_light *light, t_lcalc *c)
{
	if (light->type == LIGHT_SPOT && vec3_dot(vec3_scale(c->ld_norm, -1.0),
			light->transform.forward) < light->cutoff)
		return (false);
	if (is_in_shadow(rt->bvh, vec3_add(sha->hit->point,
				vec3_scale(sha->hit->normal, rt->settings.shadow_bias)), 
				c->ld_norm, c->dist))
		return (false);
	return (true);
}

t_vec3	calc_light(t_shading *sha, const t_rt_engine *rt, t_light light)
{
	t_vec3	ld;
	t_lcalc	c;
	t_vec3	half;
	double	s;

	ld = vec3_sub(light.transform.pos, sha->hit->point);
	c.dist = vec3_mag(ld);
	if (c.dist < 1e-8)
		return (vec3(0, 0, 0));
	c.ld_norm = vec3_scale(ld, 1.0 / c.dist);
	c.ndotl = vec3_dot(sha->hit->normal, c.ld_norm);
	if (c.ndotl < 1e-6 || !light_visible(sha, rt, &light, &c))
		return (vec3(0, 0, 0));
	half = vec3_norm(vec3_add(c.ld_norm,
				vec3_scale(sha->ray->direction, -1.0)));
	s = fmax(0.0, vec3_dot(sha->hit->normal, half));
	if (s < 1e-8)
		s = 0.0;
	else
		s = pow(s, sha->mat->specular * 100.0); /* Shininess fallback */
	return (vec3_add(pixel_color(sha->albedo, light.rgb, light.brightness
				* c.ndotl), vec3_scale(light.rgb, light.brightness
				* sha->mat->specular * s)));
}
