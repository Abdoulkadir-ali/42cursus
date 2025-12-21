/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tesselation_manager.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 22:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/17 22:30:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry.h"
#include "graphics.h"

// Forward declaration if not in geometry.h yet, but should be added.
// t_map *tesselate_mesh(t_map *src);

t_map	*generate_tesselated_map(t_map *base, int level)
{
	t_map	*current;
	t_map	*next;
	int		i;

	if (!base || level < 1)
		return (NULL);
	
	current = NULL;
	i = 0;
	while (i < level)
	{
		t_map *src = (i == 0) ? base : current;

		next = tesselate_mesh(src);
		if (!next)
		{
			// Allocation failed for next level.
			// Return current level (best effort) if it exists.
			// If even first level failed (current==NULL), return NULL.
			return (current);
		}

		if (current)
			free_map(current);
		current = next;
		i++;
	}
	return (current);
}

// Helper to copy a sub-rectangle of the map
t_map	*extract_submap(t_map *src, t_vec2 min, t_vec2 max)
{
	t_map	*sub;
	int		w;
	int		h;
	int		x;
	int		y;
	int		new_idx;
	int		old_idx;

	w = max.x - min.x + 1;
	h = max.y - min.y + 1;
	
	if (w <= 0 || h <= 0)
		return (NULL);

	sub = malloc(sizeof(t_map));
	if (!sub) return (NULL);
	
	*sub = *src; // Copy config/styles
	sub->width = w;
	sub->height = h;
	
	// Allocate points
	sub->points.pos = malloc(sizeof(t_vec3d) * w * h);
	sub->points.raw = malloc(sizeof(t_vec3d) * w * h); // Copy raw too?
	sub->points.color = malloc(sizeof(int) * w * h);
	
	if (!sub->points.pos || !sub->points.raw || !sub->points.color)
	{
		// Partial cleanup
		if (sub->points.pos) free(sub->points.pos);
		if (sub->points.raw) free(sub->points.raw);
		if (sub->points.color) free(sub->points.color);
		free(sub);
		return (NULL);
	}
	
	y = 0;
	while (y < h)
	{
		x = 0;
		while (x < w)
		{
			new_idx = y * w + x;
			old_idx = (y + min.y) * src->width + (x + min.x);
			
			sub->points.pos[new_idx] = src->points.pos[old_idx];
			sub->points.raw[new_idx] = src->points.raw[old_idx];
			sub->points.color[new_idx] = src->points.color[old_idx];
			x++;
		}
		y++;
	}
	return (sub);
}

t_map	*generate_tesselated_submap(t_map *base, t_vec2 min, t_vec2 max, int level)
{
	t_map	*sub;
	t_map	*tess;
	
	// 1. Extract visible area
	sub = extract_submap(base, min, max);
	if (!sub) return (NULL);
	
	// 2. Tesselate it
	tess = generate_tesselated_map(sub, level);
	
	// 3. Clean up intermediate sub-map base
	// Note: We need to free 'sub' but NOT the data if 'tess' reuses it?
	// generate_tesselated_map creates NEW maps. So 'sub' is fully redundant after call.
	free_map(sub);
	
	return (tess);
}
