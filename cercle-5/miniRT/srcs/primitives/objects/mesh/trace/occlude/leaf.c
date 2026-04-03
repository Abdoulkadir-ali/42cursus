/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leaf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 13:46:37 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mesh.h"

bool	leaf_occluded(t_mesh *mesh, t_mbvh_node *node, const t_ray *ray,
		double dist)
{
	size_t	i;
	size_t	tri;
	double	t;

	i = 0;
	while (i < node->count)
	{
		tri = node->left_or_first + i;
		if (intersect_tri_precomp(ray, &mesh->tri_cache[tri], &t, NULL)
			&& t < dist)
			return (true);
		i++;
	}
	return (false);
}
