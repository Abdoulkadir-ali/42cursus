/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tesselation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 22:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 03:36:44 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry.h"

/**
 * @brief Build a one-level tessellated copy of a map.
 * @param src Source map to densify.
 * @return Newly allocated tessellated map, or `NULL` on failure.
 */
t_map	*tesselate_mesh(t_map *src)
{
	size_t	new_w;
	size_t	new_h;
	t_map	*dst;

	dst = init_tesselated_map(src, &new_w, &new_h);
	if (!dst)
		return (NULL);
	if (!allocate_map_points(dst))
	{
		free(dst);
		return (NULL);
	}
	fill_tesselated_points(dst, src);
	finalize_tesselated_map(dst, src);
	return (dst);
}
