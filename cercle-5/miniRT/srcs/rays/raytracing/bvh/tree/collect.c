/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/13 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

static t_vec3	get_centroid(const t_aabb *bbox)
{
	return (vec3_scale(vec3_add(bbox->min, bbox->max), 0.5));
}

static int	get_count_for_type(int type, t_scene *scene)
{
	if (type == TYPE_ANIM)
		return (scene->anim_count);
	else if (type == TYPE_MESH)
		return (scene->mesh_count);
	else if (type == TYPE_SPHERE)
		return (scene->sphere_count);
	else if (type == TYPE_PLANE)
		return (scene->plane_count);
	else if (type == TYPE_CYLINDER)
		return (scene->cylinder_count);
	else if (type == TYPE_CONE)
		return (scene->cone_count);
	else
		return (0);
}

static void	add_items(t_build_item *items, size_t *k, int type, t_scene *scene)
{
	int	i;
	int	count;

	count = get_count_for_type(type, scene);
	if (count == 0)
		return ;
	i = 0;
	while (i < count)
	{
		items[*k].ref.type = type;
		items[*k].ref.index = i;
		items[*k].bbox = aabb_from_ref(scene, items[*k].ref);
		items[*k].centroid = get_centroid(&items[*k].bbox);
		(*k)++;
		i++;
	}
}

static size_t	collect_complex(t_scene *scene, t_build_item *items, size_t k)
{
	add_items(items, &k, TYPE_ANIM, scene);
	add_items(items, &k, TYPE_MESH, scene);
	return (k);
}

size_t	collect_objects(t_scene *scene, t_build_item *items)
{
	size_t	k;

	k = 0;
	ft_print_debug("BVH Collect: spheres=%d, planes=%d, cylinders=%d, cones=%d, meshes=%d, anim=%d\n",
		scene->sphere_count, scene->plane_count, scene->cylinder_count,
		scene->cone_count, scene->mesh_count, scene->anim_count);
	add_items(items, &k, TYPE_SPHERE, scene);
	/* Planes are handled globally, not in BVH to avoid infinite bbox issues */
	/* add_items(items, &k, TYPE_PLANE, scene); */
	add_items(items, &k, TYPE_CYLINDER, scene);
	add_items(items, &k, TYPE_CONE, scene);
	k = collect_complex(scene, items, k);
	ft_print_debug("BVH Collect Finished: total items=%zu\n", k);
	return (k);
}
