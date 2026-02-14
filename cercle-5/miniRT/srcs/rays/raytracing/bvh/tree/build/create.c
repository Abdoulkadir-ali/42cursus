/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/08 14:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "build.h"
#include "raytracing.h"

t_bvh	*bvh_create(t_scene *scene)
{
	t_bvh			*bvh;
	t_build_item	*items;
	size_t			total;
	size_t			k;

	if (!scene)
		return (NULL);
	bvh = malloc(sizeof(t_bvh));
	if (!bvh)
		return (NULL);
	bvh->scene = scene;
	total = scene->sphere_count + scene->plane_count + scene->cylinder_count
		+ scene->cone_count + scene->mesh_count;
	if (total == 0)
	{
		bvh->root = NULL;
		return (bvh);
	}
	items = malloc(sizeof(t_build_item) * total);
	if (!items)
		return (free(bvh), NULL);
	k = collect_objects(scene, items);
	bvh->root = build_recursive(items, k);
	free(items);
	return (bvh);
}

void	bvh_destroy(t_bvh *bvh)
{
	if (!bvh)
		return ;
	node_destroy(bvh->root);
	free(bvh);
}
