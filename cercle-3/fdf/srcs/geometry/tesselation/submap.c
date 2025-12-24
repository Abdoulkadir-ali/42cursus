/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   submap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/24 02:38:13 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry.h"

static void	free_submap_points(t_map *sub)
{
	if (sub->points.pos)
		free(sub->points.pos);
	if (sub->points.raw)
		free(sub->points.raw);
	if (sub->points.color)
		free(sub->points.color);
	if (sub->points.source_color)
		free(sub->points.source_color);
}

static t_map	*alloc_submap(t_map *src, int w, int h)
{
	t_map	*sub;
	int		size;

	sub = malloc(sizeof(t_map));
	if (!sub)
		return (NULL);
	*sub = *src;
	sub->width = w;
	sub->height = h;
	size = w * h;
	sub->points.pos = malloc(sizeof(t_vec3d) * size);
	sub->points.raw = malloc(sizeof(t_vec3d) * size);
	sub->points.color = malloc(sizeof(t_vec3) * size);
	sub->points.source_color = malloc(sizeof(t_vec3) * size);
	if (!sub->points.pos || !sub->points.raw || !sub->points.color
		|| !sub->points.source_color)
	{
		free_submap_points(sub);
		free(sub);
		return (NULL);
	}
	return (sub);
}

static void	copy_submap(t_map *sub, t_map *src, int w, t_vec2 min)
{
	t_vec2	pos;
	t_vec2	indices;
	int		h;

	h = sub->height;
	pos.y = 0;
	while (pos.y < h)
	{
		pos.x = 0;
		while (pos.x < w)
		{
			indices.x = pos.y * w + pos.x;
			indices.y = (pos.y + min.y) * src->width + (pos.x + min.x);
			sub->points.pos[indices.x] = src->points.pos[indices.y];
			sub->points.raw[indices.x] = src->points.raw[indices.y];
			sub->points.color[indices.x] = src->points.color[indices.y];
			sub->points.source_color[indices.x]
				= src->points.source_color[indices.y];
			pos.x++;
		}
		pos.y++;
	}
}

t_map	*extract_submap(t_map *src, t_vec2 min, t_vec2 max)
{
	t_map	*sub;
	int		w;
	int		h;

	w = max.x - min.x + 1;
	h = max.y - min.y + 1;
	if (w <= 0 || h <= 0)
		return (NULL);
	sub = alloc_submap(src, w, h);
	if (!sub)
		return (NULL);
	copy_submap(sub, src, w, min);
	return (sub);
}

t_map	*generate_tesselated_submap(t_map *base, t_vec2 min, t_vec2 max,
		int level)
{
	t_map	*sub;
	t_map	*tess;

	sub = extract_submap(base, min, max);
	if (!sub)
	{
		return (NULL);
	}
	tess = generate_tesselated_map(sub, level);
	free_map(sub);
	return (tess);
}
