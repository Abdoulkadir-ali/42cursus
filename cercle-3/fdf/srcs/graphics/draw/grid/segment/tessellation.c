/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tessellation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 20:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 02:31:56 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

/**
 * @brief Convert a tessellation step index into a 0..1 interpolation factor.
 * @param k Current tessellation step.
 * @param steps Total number of interpolation steps.
 * @return Normalized interpolation factor.
 */
static float	compute_t(int k, int steps)
{
	return ((float)k / steps);
}

/**
 * @brief Interpolate one intermediate 3D position along a segment.
 * @param v1 Start position.
 * @param v2 End position.
 * @param t Normalized interpolation factor.
 * @return Interpolated position.
 */
static t_vec3d	interpolate_position(t_vec3d v1, t_vec3d v2, float t)
{
	t_vec3d	v_curr;

	v_curr.x = v1.x + (v2.x - v1.x) * t;
	v_curr.y = v1.y + (v2.y - v1.y) * t;
	v_curr.z = v1.z + (v2.z - v1.z) * t;
	return (v_curr);
}

/**
 * @brief Build one transformable point from interpolated position and color.
 * @param v_curr Interpolated map-space position.
 * @param color Interpolated color.
 * @param g Graphics state providing z-divisor settings.
 * @return Point ready for `apply_transform`.
 */
static t_point	create_point(t_vec3d v_curr, t_vec3 color, t_graphics *g)
{
	if (g->camera->use_z_divisor && g->map->z_divisor != 0)
		v_curr.z /= (double)g->map->z_divisor;
	return ((t_point){.pos = v_curr, .color = color});
}

/**
 * @brief Draw one interpolated step inside a tessellated segment.
 * @param t_ctx Tessellation state for the current segment.
 * @param g Graphics state providing transforms and draw helpers.
 */
static void	process_tessellation_step(t_tessellation_ctx *t_ctx, t_graphics *g)
{
	float			t;
	t_vec3d			v_curr;
	t_vec3			color;
	t_point			p_input;

	t = compute_t(t_ctx->k, t_ctx->steps);
	v_curr = interpolate_position(t_ctx->v1, t_ctx->v2, t);
	color = interpolate_color(t_ctx->c1, t_ctx->c2, (double)t);
	p_input = create_point(v_curr, color, g);
	t_ctx->curr = apply_transform(p_input, g->camera);
	if (should_draw_line(t_ctx->prev, t_ctx->curr, g))
		draw_line(g, t_ctx->prev, t_ctx->curr);
	t_ctx->prev = t_ctx->curr;
}

/**
 * @brief Draw a subdivided segment when sub-unit LOD is active.
 * @param ctx Segment context containing the resolved neighbor coordinates.
 * @param g Graphics state providing render configuration and transforms.
 * @param params Segment source parameters.
 */
void	draw_tessellated_segment(t_segment_ctx *ctx, t_graphics *g,
		t_draw_line_params params)
{
	t_tessellation_ctx	t_ctx;

	t_ctx = init_tessellation_ctx(ctx, g, params);
	if (t_ctx.steps <= 1)
		return ;
	while (t_ctx.k <= t_ctx.steps)
	{
		process_tessellation_step(&t_ctx, g);
		t_ctx.k++;
	}
}
