/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 22:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 03:36:44 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry.h"
#include "graphics.h"

/**
 * @brief Apply multiple tessellation passes to a base map.
 * @param base Source map to densify.
 * @param level Number of tessellation passes to apply.
 * @return Last generated tessellated map, or `NULL` on failure.
 */
t_map	*generate_tesselated_map(t_map *base, int level)
{
	t_map	*current;
	t_map	*next;
	t_map	*src;
	int		i;

	if (!base || level < 1)
		return (NULL);
	current = NULL;
	i = 0;
	while (i < level)
	{
		if (i == 0)
			src = base;
		else
			src = current;
		next = tesselate_mesh(src);
		if (!next)
			return (current);
		if (current)
			free_map(current);
		current = next;
		i++;
	}
	return (current);
}
