/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 10:38:58 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

static double	light_att(double d_sq)
{
    return (1.0 / (1.0 + ATTENUATION_K * (d_sq)));
}

void	apply_emissive_hit(t_shading *ctx, t_vec3 *total, t_material *m, t_vec3 lrad)
{
	t_vec3	ldir;
	double	c[4];

	if (vec3_mag_sq(ctx->aux_v) > MAX_EMISSIVE_DIST_SQ)
		return ;
	c[0] = vec3_mag(ctx->aux_v) - lrad.x - EMISSIVE_SURF_OFF;
	ldir = vec3_norm(ctx->aux_v);
	c[1] = vec3_dot(ctx->hit->normal, ldir);
	if (c[0] <= 0.0 || c[1] < NDOTL_MIN)
		return ;
	if (is_in_shadow(ctx->bvh, vec3_add(ctx->hit->point, vec3_scale(
					ctx->hit->normal, fmax(MAG_EPSILON, MAG_EPSILON
						* EPSILON_MUL * (1 - c[1])))), ldir, c[0]))
		return ;
	c[2] = vec3_mag(m->emission) / COLOR_MAX * fmax(lrad.x, HALF_SCALE)
		* EMISSIVE_BR_SCALE;
	c[3] = fmax(0.0, vec3_dot(ctx->hit->normal, vec3_norm(vec3_add(ldir,
						vec3_scale(ctx->ray->direction, -1.0)))));
	if (c[3] < NDOTH_MIN)
		c[3] = 0.0;
	else
		c[3] = powf((float)c[3], (float)ctx->mat.shininess);
	*total = vec3_add(*total, vec3_add(pixel_color(ctx->albedo, m->emission,
					c[2] * c[1] * light_att(c[0] * c[0])), vec3_scale(
					m->emission, c[2] * ctx->mat.specular
					* light_att(c[0] * c[0]) * c[3])));
}
