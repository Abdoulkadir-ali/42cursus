/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tesselation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 22:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/23 17:52:06 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "geometry.h"

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
