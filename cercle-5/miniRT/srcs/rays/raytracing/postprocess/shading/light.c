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
** Calculates lighting contribution for a single light source.
*/
t_vec3	calc_light(t_shading_ctx *ctx, t_light light)
{
	t_vec3	ld;
	double	ndotl;
	t_vec3	half;
	double	spec;
	double	bias;

	ld = vec3_sub(light.transform.pos, ctx->hit->point);
	ld = vec3_norm(ld);
	ndotl = vec3_dot(ctx->hit->normal, ld);
	if (ndotl <= 0.0)
		return (vec3(0, 0, 0));
	if (light.type == LIGHT_SPOT && vec3_dot(vec3_scale(ld, -1.0),
			light.transform.forward) < light.cutoff)
		return (vec3(0, 0, 0));
	bias = fmax(EPSILON, EPSILON * 10.0 * (1.0 - ndotl));
	if (is_in_shadow(ctx->bvh, vec3_add(ctx->hit->point,
				vec3_scale(ctx->hit->normal, bias)),
			vec3_sub(light.transform.pos, ctx->hit->point)))
		return (vec3(0, 0, 0));
	half = vec3_norm(vec3_add(ld, vec3_scale(ctx->ray->direction, -1.0)));
	spec = pow(fmax(0.0, vec3_dot(ctx->hit->normal, half)), ctx->mat.shininess);
	return (vec3_add(pixel_color(ctx->albedo, light.rgb, light.brightness
				* ndotl), vec3_scale(light.rgb, light.brightness
				* ctx->mat.specular * spec)));
}
