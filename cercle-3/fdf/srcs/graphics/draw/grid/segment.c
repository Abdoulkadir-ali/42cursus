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



void	draw_segment(t_graphics *g, t_draw_line_params params,
		int is_horizontal)
{
	t_segment_ctx	ctx;
	t_point			p2;

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
				// Apply Z Divisor if enabled
				if (g->camera->use_z_divisor && g->map->z_divisor != 0.0)
					v_curr.z /= g->map->z_divisor;
					
				t_point p_input = {v_curr, color};
				// Z-Scale applied in apply_transform
				curr = apply_transform(p_input, g->camera);
				
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

	else if (g->render_config.render_mode == RENDER_LINES)
		draw_line(g, params.p1, p2);
}
