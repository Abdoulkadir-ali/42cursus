/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leaf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/13 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

/*
** Helper function to process leaf nodes for intersection.
*/
void	process_leaf(const t_bvh_node *node, const t_ray *ray, const t_bvh *bvh,
		t_hit *hit)
{
	size_t	i;
	t_hit	temp_hit;

	i = 0;
	while (i < node->num_refs)
	{
		temp_hit.t = MAX_VALUE;
		temp_hit.ref.type = TYPE_NONE;
		if (intersect_object(ray, bvh->scene, node->refs[i], &temp_hit)
			&& temp_hit.t < hit->t)
			*hit = temp_hit;
		i++;
	}
}
