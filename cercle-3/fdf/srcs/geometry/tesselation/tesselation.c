/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tesselation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 22:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/21 00:26:59 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry.h"
#include "color.h"

static t_vec3d	mix_pos(t_vec3d p1, t_vec3d p2, double ratio)
{
	t_vec3d	res;

	res.x = p1.x + (p2.x - p1.x) * ratio;
	res.y = p1.y + (p2.y - p1.y) * ratio;
	res.z = p1.z + (p2.z - p1.z) * ratio;
	return (res);
}

static void	set_point(t_map *dst, int x, int y, t_vec3d pos, int color)
{
	int	idx;

	idx = y * dst->width + x;
	dst->points.raw[idx] = pos;
	dst->points.pos[idx] = pos;
	dst->points.color[idx] = color;
}

static void	compute_tesselated_point(t_map *src, t_map *dst, int x, int y)
{
	int		sx;
	int		sy;
	int		idx;
	t_vec3d	p1;
	t_vec3d	p2;
	int		c1;
	int		c2;

	sx = x / 2;
	sy = y / 2;
	idx = sy * src->width + sx;
	// Direct copy
	if (x % 2 == 0 && y % 2 == 0)
	{
		set_point(dst, x, y, src->points.raw[idx], src->points.color[idx]);
		return ;
	}
	// Horizontal split
	if (x % 2 != 0 && y % 2 == 0)
	{
		if (sx + 1 >= (int)src->width)
		{
			set_point(dst, x, y, src->points.raw[idx], src->points.color[idx]);
			return ;
		}
		p1 = src->points.raw[idx];
		p2 = src->points.raw[idx + 1];
		c1 = src->points.color[idx];
		c2 = src->points.color[idx + 1];
		set_point(dst, x, y, mix_pos(p1, p2, 0.5), interpolate_color(c1, c2, 0.5));
		return ;
	}
	// Vertical split
	if (x % 2 == 0 && y % 2 != 0)
	{
		if (sy + 1 >= (int)src->height)
		{
			set_point(dst, x, y, src->points.raw[idx], src->points.color[idx]);
			return ;
		}
		p1 = src->points.raw[idx];
		p2 = src->points.raw[idx + src->width];
		c1 = src->points.color[idx];
		c2 = src->points.color[idx + src->width];
		set_point(dst, x, y, mix_pos(p1, p2, 0.5), interpolate_color(c1, c2, 0.5));
		return ;
	}
	// Center split (Average of 4, or simpler: Average of Diagonal)
	// We use average of horizontal neighbors on the new grid? No, use source diags.
	if (x % 2 != 0 && y % 2 != 0)
	{
		if (sx + 1 >= (int)src->width || sy + 1 >= (int)src->height)
		{
			set_point(dst, x, y, src->points.raw[idx], src->points.color[idx]);
			return ;
		}
		// Interp between TopLeft and BottomRight
		p1 = src->points.raw[idx];
		p2 = src->points.raw[idx + src->width + 1];
		c1 = src->points.color[idx];
		c2 = src->points.color[idx + src->width + 1];
		
		t_vec3d res1 = mix_pos(p1, p2, 0.5);
		int col1 = interpolate_color(c1, c2, 0.5);
		
		// Optional: Interp between TopRight and BottomLeft for better accuracy
		t_vec3d p3 = src->points.raw[idx + 1];
		t_vec3d p4 = src->points.raw[idx + src->width];
		int c3 = src->points.color[idx + 1];
		int c4 = src->points.color[idx + src->width];

		t_vec3d res2 = mix_pos(p3, p4, 0.5);
		int col2 = interpolate_color(c3, c4, 0.5);

		set_point(dst, x, y, mix_pos(res1, res2, 0.5), interpolate_color(col1, col2, 0.5));
	}
}

t_map	*tesselate_mesh(t_map *src)
{
	t_map	*dst;
	size_t	new_w;
	size_t	new_h;

	new_w = src->width * 2 - 1;
	new_h = src->height * 2 - 1;
	if (new_w < src->width || new_h < src->height) // Overflow check loosely
		return (NULL);
	dst = malloc(sizeof(t_map));
	if (!dst)
		return (NULL);
	dst->width = new_w;
	dst->height = new_h;
	dst->z_divisor = src->z_divisor;
	dst->style = src->style;
	if (!allocate_map_points(dst))
	{
		free(dst);
		return (NULL);
	}
	size_t	y = 0;
	while (y < new_h)
	{
		size_t	x = 0;
		while (x < new_w)
		{
			compute_tesselated_point(src, dst, x, y);
			x++;
		}
		y++;
	}
	dst->min_max_z = src->min_max_z; // Approx
	dst->min_proj_z = src->min_proj_z;
	dst->max_proj_z = src->max_proj_z;
	return (dst);
}
