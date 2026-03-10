/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visibility.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 16:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 01:21:29 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"
#include "render.h"

/**
 * @brief Expand a projected bounding box with one projected point.
 * @param p Projected point to include.
 * @param min Current minimum projected bound.
 * @param max Current maximum projected bound.
 */
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

/**
 * @brief Project one 3D map point through the active camera transform.
 * @param p3d Source 3D point.
 * @param color Source packed color.
 * @param g Graphics context providing camera and map state.
 * @return Projected point ready for screen-space use.
 */
t_point	project_helper(t_vec3d p3d, int color, t_graphics *g)
{
	t_point	p;

	if (p3d.z <= BAD_VALUE + 1.0)
		return ((t_point){.pos = {BAD_VALUE, BAD_VALUE, BAD_VALUE},
			.color = int_color_to_rgb(color)});
	if (g->camera->use_z_divisor && g->map->z_divisor != 0)
		p3d.z /= (double)g->map->z_divisor;
	p = (t_point){.pos = p3d, .color = int_color_to_rgb(color)};
	return (apply_transform(p, g->camera));
}

/**
 * @brief Compute the projected screen-space bounds of the map volume.
 * @param g Graphics context providing map bounds and camera state.
 * @param min Output minimum projected bound.
 * @param max Output maximum projected bound.
 */
static void	compute_projected_bounds(t_graphics *g, t_vec2 *min, t_vec2 *max)
{
	t_vec3d	c[8];
	int		i;
	t_point	p;

	c[0] = (t_vec3d){0, 0, g->map->min_max_z.x};
	c[1] = (t_vec3d){g->map->width, 0, g->map->min_max_z.x};
	c[2] = (t_vec3d){0, g->map->height, g->map->min_max_z.x};
	c[3] = (t_vec3d){g->map->width, g->map->height, g->map->min_max_z.x};
	c[4] = (t_vec3d){0, 0, g->map->min_max_z.y};
	c[5] = (t_vec3d){g->map->width, 0, g->map->min_max_z.y};
	c[6] = (t_vec3d){0, g->map->height, g->map->min_max_z.y};
	c[7] = (t_vec3d){g->map->width, g->map->height, g->map->min_max_z.y};
	*min = (t_vec2){2000000000, 2000000000};
	*max = (t_vec2){-2000000000, -2000000000};
	i = 0;
	while (i < 8)
	{
		p = project_helper(c[i++], 0, g);
		if (p.pos.x > BAD_VALUE + 10)
			update_bounds(p, min, max);
	}
}

/**
 * @brief Check whether the active map bounding volume overlaps the viewport.
 * @param g Graphics context providing the active map, window, and camera.
 * @return `1` when the map may be visible, otherwise `0`.
 */
int	is_map_visible(t_graphics *g)
{
	t_vec2	min;
	t_vec2	max;

	if (!g || !g->map)
		return (0);
	calculate_transform_matrix(g->camera);
	compute_projected_bounds(g, &min, &max);
	if (max.x < 0 || min.x > (int)g->window->width || max.y < 0
		|| min.y > (int)g->window->height)
		return (0);
	return (1);
}
