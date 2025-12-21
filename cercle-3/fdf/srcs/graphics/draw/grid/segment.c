/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 12:46:31 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/21 00:33:24 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

static void	compute_next_coords(t_segment_ctx *ctx, t_draw_line_params params,
		int is_horizontal)
{
	if (is_horizontal)
	{
		ctx->next_x = params.x + params.step;
		ctx->next_y = params.y;
	}
	else
	{
		ctx->next_x = params.x;
		ctx->next_y = params.y + params.step;
	}
}

static void	compute_prev_next(t_segment_ctx *ctx, t_graphics *g,
		t_draw_line_params params, int is_horizontal)
{
	if (is_horizontal)
	{
		ctx->prev_coord = params.x - params.step;
		ctx->next_coord = ctx->next_x + params.step;
		ctx->max_coord = (int)g->map->width;
	}
	else
	{
		ctx->prev_coord = params.y - params.step;
		ctx->next_coord = ctx->next_y + params.step;
		ctx->max_coord = (int)g->map->height;
	}
}

static void	compute_p0_p3(t_segment_ctx *ctx, t_graphics *g,
		t_draw_line_params params, t_point p2)
{
	if (ctx->prev_coord >= 0)
	{
		if (ctx->prev_coord == params.x - params.step)
			ctx->p0 = get_cached_proj(g, ctx->prev_coord, params.y);
		else
			ctx->p0 = get_cached_proj(g, params.x, ctx->prev_coord);
	}
	else
		ctx->p0 = params.p1;
	if (ctx->next_coord < (size_t)ctx->max_coord)
	{
		if (ctx->next_coord == ctx->next_x + params.step)
			ctx->p3 = get_cached_proj(g, ctx->next_coord, params.y);
		else
			ctx->p3 = get_cached_proj(g, params.x, ctx->next_coord);
	}
	else
		ctx->p3 = p2;
}

void	draw_segment(t_graphics *g, t_draw_line_params params,
		int is_horizontal)
{
	t_segment_ctx	ctx;
	t_point			p2;
	t_spline		spline;

	compute_next_coords(&ctx, params, is_horizontal);
	if (ctx.next_x >= g->map->width || ctx.next_y >= g->map->height)
		return ;
	
	// Check LOD for On-the-Fly Tessellation
	// Only apply for Lines mode and when detail is required (lod < 1.0)
	if (g->render_config.render_mode == RENDER_LINES && g->render_config.lod_value < 1.0)
	{
		int steps = (int)(1.0 / g->render_config.lod_value);
		if (steps > 1)
		{
			// Limit steps to respect ~300k points (Safety)
			// Total Points ~= 2 * W * H * steps.
			// Max Steps = 300000 / (2 * W * H).
			long total_base = (long)g->map->width * g->map->height;
			int max_steps = 300000 / (2 * total_base);
			if (max_steps < 2) max_steps = 2; // Allow at least 2x if zoomed in
			if (steps > max_steps) steps = max_steps;
			if (steps > 16) steps = 16; // Hard clamp for performance

			t_vec3d v1 = g->map->points.pos[params.y * g->map->width + params.x];
			t_vec3d v2 = g->map->points.pos[ctx.next_y * g->map->width + ctx.next_x];
			unsigned int c1 = g->map->points.color[params.y * g->map->width + params.x];
			unsigned int c2 = g->map->points.color[ctx.next_y * g->map->width + ctx.next_x];
			
			t_point prev = params.p1;
			t_point curr;
			
			int k = 1;
			while (k <= steps)
			{
				float t = (float)k / steps;
				
				// Lerp Position
				t_vec3d v_curr;
				v_curr.x = v1.x + (v2.x - v1.x) * t;
				v_curr.y = v1.y + (v2.y - v1.y) * t;
				v_curr.z = v1.z + (v2.z - v1.z) * t;
				
				// Lerp Color (Simple Int Lerp)
			// interpolate channels separately for better visuals
			unsigned int color;
			{
				unsigned int r1 = (c1 >> 16) & 0xFF;
				unsigned int g1c = (c1 >> 8) & 0xFF;
				unsigned int b1 = c1 & 0xFF;
				unsigned int r2c = (c2 >> 16) & 0xFF;
				unsigned int g2c = (c2 >> 8) & 0xFF;
				unsigned int b2c = c2 & 0xFF;
				unsigned int rr = r1 + (unsigned int)((r2c - r1) * t);
				unsigned int gg = g1c + (unsigned int)((g2c - g1c) * t);
				unsigned int bb = b1 + (unsigned int)((b2c - b1) * t);
				color = (rr << 16) | (gg << 8) | bb;
			}
				curr = project_point(v_curr, color, g->camera, g->map->z_divisor);
				
				// Visibility Check (On Segment) needed?
				// If p1 and p2 were onscreen, midpoints likely on screen.
				// If p1/p2 offscreen, midpoints might be onscreen?
				// We assume cached projection check covered endpoints.
				// For tessellation, we just draw.
				if (should_draw_line(prev, curr, g))
					draw_line(g, prev, curr);
				
				prev = curr;
				k++;
			}
			return;
		}
	}

	// Fallback / Standard Logic
	p2 = get_cached_proj(g, ctx.next_x, ctx.next_y);
	if (!should_draw_line(params.p1, p2, g))
		return ;
	if (g->render_config.render_mode == RENDER_SPLINES)
	{
		compute_prev_next(&ctx, g, params, params.step == 1);
		compute_p0_p3(&ctx, g, params, p2);
		spline = (t_spline){ctx.p0, params.p1, p2, ctx.p3};
		draw_spline_segment(g, spline, g->camera->spline_segments);
	}
	else if (g->render_config.render_mode == RENDER_LINES)
		draw_line(g, params.p1, p2);
}
