/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 15:10:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/24 02:27:12 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry.h"

t_map	*init_tesselated_map(t_map *src, size_t *new_w, size_t *new_h)
{
	t_map	*dst;

	*new_w = src->width * 2 - 1;
	*new_h = src->height * 2 - 1;
	if (*new_w < src->width || *new_h < src->height)
		return (NULL);
	dst = malloc(sizeof(t_map));
	if (!dst)
		return (NULL);
	dst->width = *new_w;
	dst->height = *new_h;
	dst->z_divisor = src->z_divisor;
	dst->style = src->style;
	return (dst);
}

void	fill_tesselated_points(t_map *dst, t_map *src)
{
	size_t	y;
	size_t	x;
	t_vec2	pos;

	y = 0;
	while (y < dst->height)
	{
		x = 0;
		while (x < dst->width)
		{
			pos.x = x++;
			pos.y = y;
			compute_tesselated_point(src, dst, pos);
		}
		y++;
	}
}

void	finalize_tesselated_map(t_map *dst, t_map *src)
{
	dst->min_max_z = src->min_max_z;
	dst->min_proj_z = src->min_proj_z;
	dst->max_proj_z = src->max_proj_z;
}
