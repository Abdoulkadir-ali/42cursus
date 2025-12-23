/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bounds.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 16:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/23 17:19:15 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"
#include "render.h"

static void	update_bounds_for_point(size_t x, size_t y, t_graphics *g,
		t_update_ctx *ctx)
{
	t_vec3d	p3d;
	t_point	p;

	p3d = g->base_map->points.pos[y * g->base_map->width + x];
	p = project_helper(p3d, 0, g);
	if (p.pos.x > BAD_VALUE + 10 && is_on_screen((t_vec2){p.pos.x, p.pos.y}, g))
	{
		if ((int)x < ctx->min->x)
			ctx->min->x = (int)x;
		if ((int)x > ctx->max->x)
			ctx->max->x = (int)x;
		if ((int)y < ctx->min->y)
			ctx->min->y = (int)y;
		if ((int)y > ctx->max->y)
			ctx->max->y = (int)y;
	}
}

static void	process_points(t_graphics *g, t_vec2 *min, t_vec2 *max)
{
	size_t			x;
	size_t			y;
	int				stride;
	t_update_ctx	ctx;

	ctx.min = min;
	ctx.max = max;
	stride = 4;
	y = 0;
	while (y < g->base_map->height)
	{
		x = 0;
		while (x < g->base_map->width)
		{
			update_bounds_for_point(x, y, g, &ctx);
			x += stride;
		}
		y += stride;
	}
}

static void	handle_fallback(t_graphics *g, t_vec2 *min, t_vec2 *max)
{
	int	cx;
	int	cy;

	cx = g->base_map->width / 2;
	cy = g->base_map->height / 2;
	min->x = cx - 5;
	max->x = cx + 5;
	min->y = cy - 5;
	max->y = cy + 5;
}

static void	clamp_to_map(t_graphics *g, t_vec2 *min, t_vec2 *max)
{
	if (min->x < 0)
		min->x = 0;
	if (max->x >= (int)g->base_map->width)
		max->x = (int)g->base_map->width - 1;
	if (min->y < 0)
		min->y = 0;
	if (max->y >= (int)g->base_map->height)
		max->y = (int)g->base_map->height - 1;
}

void	get_visible_map_bounds(t_graphics *g, t_vec2 *min, t_vec2 *max)
{
	min->x = (int)g->base_map->width;
	max->x = 0;
	min->y = (int)g->base_map->height;
	max->y = 0;
	process_points(g, min, max);
	if (min->x > max->x)
		handle_fallback(g, min, max);
	else
	{
		min->x -= 4 * 2;
		max->x += 4 * 2;
		min->y -= 4 * 2;
		max->y += 4 * 2;
	}
	clamp_to_map(g, min, max);
}
