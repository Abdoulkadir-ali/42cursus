/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 11:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 07:40:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

extern t_aabb	aabb_union(t_aabb a, t_aabb b);

/**
 * @brief Computes global_aabb from current sub-shape world positions.
 * Updates the body boundary each frame to reflect child movement.
 */
void	update_compound(t_physics_body *b)
{
	size_t	i;
	t_aabb	acc;

	if (!b->is_compound || b->sub_count == 0)
		return ;
	acc = b->sub_shapes[0].local_aabb;
	i = 1;
	while (i < b->sub_count)
	{
		acc = aabb_union(acc, b->sub_shapes[i].local_aabb);
		i++;
	}
	b->global_aabb = acc;
}
