/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   culling.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 20:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/21 00:26:59 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "graphics.h"

int	is_point_visible(t_vec3d p, t_graphics *g)
{
	int		threshold;
	double	raw_z;

	if (p.z <= DRAW_LIMIT)
		return (0);
	threshold = g->camera->dampening_threshold;
	if (threshold == 0)
		return (1);
	raw_z = p.z;
	if (threshold < 0)
		return (raw_z >= -threshold);
	else
		return (raw_z <= threshold);
}

int	is_visible(int x, int y, t_graphics *g)
{
	(void)x;
	(void)y;
	return (x >= 0 && x < (int)g->window->width && y >= 0 && y < (int)g->window->height);
}

int	is_on_screen(int x, int y, t_graphics *g)
{
	int	margin;

	margin = g->camera->frustum_margin;
	return (x >= -margin && x < (int)g->window->width + margin && y >= -margin
		&& y < (int)g->window->height + margin);
}

int	should_draw_line(t_point p1, t_point p2, t_graphics *g)
{
	if (p1.pos.x <= DRAW_LIMIT || p1.pos.y <= DRAW_LIMIT
		|| p1.pos.z <= DRAW_LIMIT || p2.pos.x <= DRAW_LIMIT
		|| p2.pos.y <= DRAW_LIMIT || p2.pos.z <= DRAW_LIMIT)
		return (0);
	if (!is_on_screen(p1.pos.x, p1.pos.y, g) && !is_on_screen(p2.pos.x,
			p2.pos.y, g))
	{
		if ((p1.pos.x < 0 && p2.pos.x < 0) || (p1.pos.x > g->window->width
				&& p2.pos.x > g->window->width) || (p1.pos.y < 0
				&& p2.pos.y < 0) || (p1.pos.y > g->window->height
				&& p2.pos.y > g->window->height))
			return (0);
	}
	return (1);
}

static void	update_bounds(t_point p, t_vec2 *min, t_vec2 *max)
{
	if (p.pos.x < min->x)
		min->x = p.pos.x;
	if (p.pos.x > max->x)
		max->x = p.pos.x;
	if (p.pos.y < min->y)
		min->y = p.pos.y;
	if (p.pos.y > max->y)
		max->y = p.pos.y;
}

int	is_map_visible(t_graphics *g)
{
	t_vec3d	c[8];
	t_vec2	min;
	t_vec2	max;
	int		i;
	t_point	p;

	if (!g || !g->map)
		return (0);
	c[0] = (t_vec3d){0, 0, g->map->min_max_z.x};
	c[1] = (t_vec3d){g->map->width, 0, g->map->min_max_z.x};
	c[2] = (t_vec3d){0, g->map->height, g->map->min_max_z.x};
	c[3] = (t_vec3d){g->map->width, g->map->height, g->map->min_max_z.x};
	c[4] = (t_vec3d){0, 0, g->map->min_max_z.y};
	c[5] = (t_vec3d){g->map->width, 0, g->map->min_max_z.y};
	c[6] = (t_vec3d){0, g->map->height, g->map->min_max_z.y};
	c[7] = (t_vec3d){g->map->width, g->map->height, g->map->min_max_z.y};
	min = (t_vec2){2000000000, 2000000000};
	max = (t_vec2){-2000000000, -2000000000};
	i = 0;
	while (i < 8)
	{
		p = project_point(c[i], 0, g->camera, g->map->z_divisor);
		if (p.pos.x > BAD_VALUE + 10)
			update_bounds(p, &min, &max);
		i++;
	}
	if (max.x < 0 || min.x > (int)g->window->width || max.y < 0
		|| min.y > (int)g->window->height)
		return (0);
	return (1);
}

void	get_visible_map_bounds(t_graphics *g, t_vec2 *min, t_vec2 *max)
{
	size_t	x;
	size_t	y;
	t_vec3d	p3d;
	t_point	p;
	int		stride;

	// Defaults: "Inverse" range
	min->x = (int)g->base_map->width;
	max->x = 0;
	min->y = (int)g->base_map->height;
	max->y = 0;

	// Optimization: If map is small (< 1000 points), stride 1. Else stride 5.
	// Actually stride 5 is fine always for > 200 points.
	stride = 4; 
	
	// Scan Grid
	y = 0;
	while (y < g->base_map->height)
	{
		x = 0;
		while (x < g->base_map->width)
		{
			p3d = g->base_map->points.pos[y * g->base_map->width + x];
			p = project_point(p3d, 0, g->camera, g->base_map->z_divisor);
			
			if (p.pos.x > BAD_VALUE + 10 && is_on_screen((int)p.pos.x, (int)p.pos.y, g))
			{
				if ((int)x < min->x) min->x = (int)x;
				if ((int)x > max->x) max->x = (int)x;
				if ((int)y < min->y) min->y = (int)y;
				if ((int)y > max->y) max->y = (int)y;
			}
			x += stride;
		}
		y += stride;
	}

	// Validate results
	if (min->x > max->x) // Nothing found visible?
	{
		// Fallback: If nothing visible, maybe we are zooming into a hole or everything is off screen.
		// Retain full map or center 10x10?
		// Let's fallback to center of map.
		int cx = g->base_map->width / 2;
		int cy = g->base_map->height / 2;
		min->x = cx - 5; max->x = cx + 5;
		min->y = cy - 5; max->y = cy + 5;
	}
	else
	{
		// Expand bounds to cover stride gaps + margin
		min->x -= stride * 2;
		max->x += stride * 2;
		min->y -= stride * 2;
		max->y += stride * 2;
	}

	// Clamp to map limits
	if (min->x < 0) min->x = 0;
	if (max->x >= (int)g->base_map->width) max->x = (int)g->base_map->width - 1;
	if (min->y < 0) min->y = 0;
	if (max->y >= (int)g->base_map->height) max->y = (int)g->base_map->height - 1;
}

int	is_backface(t_point p1, t_point p2, t_point p3)
{
	double	v1x;
	double	v1y;
	double	v2x;
	double	v2y;
	double	cross_z;

	v1x = p2.pos.x - p1.pos.x;
	v1y = p2.pos.y - p1.pos.y;
	v2x = p3.pos.x - p1.pos.x;
	v2y = p3.pos.y - p1.pos.y;
	cross_z = v1x * v2y - v1y * v2x;
	return (cross_z <= 0);
}
