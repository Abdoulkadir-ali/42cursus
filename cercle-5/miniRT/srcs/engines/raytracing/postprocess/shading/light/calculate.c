/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calclight.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/13 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

static bool	light_visible(t_shading *ctx, t_light *light, t_lcalc *c)
{
	double	bias;

	if (light->type == LIGHT_SPOT && vec3_dot(vec3_scale(c->ld_norm, -1.0),
			light->transform.forward) < light->cutoff)
		return (false);
	if (light->type == LIGHT_EMISSIVE)
		return (true);
	bias = fmax(MAG_EPSILON, MAG_EPSILON * EPSILON_MUL * (1.0 - c->ndotl));
	if (is_in_shadow(ctx->bvh, vec3_add(ctx->hit->point,
				vec3_scale(ctx->hit->normal, bias)), c->ld_norm, c->dist))
		return (false);
	return (true);
}

t_vec3	calc_light(t_shading *ctx, t_light light)
{
	t_vec3	ld;
	t_lcalc	c;
	t_vec3	half;
	double	s;

	ld = vec3_sub(light.transform.pos, ctx->hit->point);
	c.dist = vec3_mag(ld);
	if (c.dist < 1e-8)
		return (vec3(0, 0, 0));
	c.ld_norm = vec3_scale(ld, 1.0 / c.dist);
	c.ndotl = vec3_dot(ctx->hit->normal, c.ld_norm);
	if (c.ndotl < NDOTL_MIN || !light_visible(ctx, &light, &c))
		return (vec3(0, 0, 0));
	half = vec3_norm(vec3_add(c.ld_norm,
				vec3_scale(ctx->ray->direction, -1.0)));
	s = fmax(0.0, vec3_dot(ctx->hit->normal, half));
	if (s < NDOTH_MIN)
		s = 0.0;
	else
		s = pow(s, ctx->mat->shininess);
	return (vec3_add(pixel_color(ctx->albedo, light.rgb, light.brightness
				* c.ndotl), vec3_scale(light.rgb, light.brightness
				* ctx->mat->specular * s)));
}
