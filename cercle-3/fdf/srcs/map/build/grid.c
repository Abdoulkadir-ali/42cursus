/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:28:05 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/13 16:58:02 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "map.h"

static void	handle_min_max(t_process_proj_row_ctx *p)
{
	if (p->min_max_ctx->first)
	{
		p->map->min_proj_z = p->min_max_ctx->z;
		p->map->max_proj_z = p->min_max_ctx->z;
		p->min_max_ctx->first = 0;
	}
	else
	{
		if (p->min_max_ctx->z < p->map->min_proj_z)
			p->map->min_proj_z = p->min_max_ctx->z;
		if (p->min_max_ctx->z > p->map->max_proj_z)
			p->map->max_proj_z = p->min_max_ctx->z;
	}
}

static void	process_proj_row(t_process_proj_row_ctx *p, t_camera *camera)
{
	size_t	idx;
	t_vec3d	pos;
	int		color;

	p->min_max_ctx->pos.y = p->y;
	p->min_max_ctx->pos.x = 0;
	while (p->min_max_ctx->pos.x < p->map->width)
	{
		idx = (size_t)p->min_max_ctx->pos.y * p->map->width
			+ p->min_max_ctx->pos.x;
		p->min_max_ctx->idx = idx;
		pos = p->map->points.pos[idx];
		color = p->map->points.color[idx];
		p->min_max_ctx->z = project_point(pos, color, camera,
				p->z_divisor).pos.z;
		handle_min_max(p);
		p->min_max_ctx->pos.x++;
	}
}

void	calculate_min_max_proj_z(t_map *map, t_camera *camera, double z_divisor)
{
	t_min_max_ctx			ctx;
	int						y;
	t_process_proj_row_ctx	p;

	ctx.first = 1;
	y = 0;
	while (y < map->height)
	{
		p.min_max_ctx = &ctx;
		p.map = map;
		p.z_divisor = z_divisor;
		p.y = y;
		process_proj_row(&p, camera);
		y++;
	}
}

t_map	*create_test_grid(void)
{
	t_map	*map;
	float	min_z;
	float	max_z;

	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->width = 50;
	map->height = 50;
	if (!allocate_map_arrays(map))
		return (NULL);
	init_grid_points(map);
	find_min_max_z(map, &min_z, &max_z);
	map->min_max_z.x = min_z;
	map->min_max_z.y = max_z;
	calculate_z_divisor(map);
	map->min_proj_z = map->min_max_z.x;
	map->max_proj_z = map->min_max_z.y;
	return (map);
}

void	free_map(t_map *map)
{
	if (!map)
		return ;
	if (map->points.pos)
		free(map->points.pos);
	if (map->points.raw)
		free(map->points.raw);
	if (map->points.color)
		free(map->points.color);
	free(map);
}
