/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tessellation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 20:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/23 19:59:52 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

static float	compute_t(int k, int steps)
{
	return ((float)k / steps);
}

static t_vec3d	interpolate_position(t_vec3d v1, t_vec3d v2, float t)
{
	t_vec3d	v_curr;

	v_curr.x = v1.x + (v2.x - v1.x) * t;
	v_curr.y = v1.y + (v2.y - v1.y) * t;
	v_curr.z = v1.z + (v2.z - v1.z) * t;
	return (v_curr);
}

static t_point	create_point(t_vec3d v_curr, t_vec3 color, t_graphics *g)
{
	if (g->camera->use_z_divisor && g->map->z_divisor != 0.0)
		v_curr.z /= g->map->z_divisor;
	return ((t_point){.pos = v_curr, .color = color});
}

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
