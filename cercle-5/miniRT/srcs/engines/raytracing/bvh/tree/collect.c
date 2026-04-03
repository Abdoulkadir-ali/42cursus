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
		return ((int)scene->anim_count);
	else if (type == TYPE_MESH)
		return ((int)scene->mesh_count);
	else if (type == TYPE_SPHERE)
		return ((int)scene->sphere_count);
	else if (type == TYPE_PLANE)
		return ((int)scene->plane_count);
	else if (type == TYPE_CYLINDER)
		return ((int)scene->cylinder_count);
	else if (type == TYPE_CONE)
		return ((int)scene->cone_count);
	else if (type == TYPE_TRI)
		return ((int)scene->tri_count);
	else if (type == TYPE_RECT)
		return ((int)scene->rect_count);
	else if (type == TYPE_PYRAMID)
		return ((int)scene->pyramid_count);
	else if (type == TYPE_BOX)
		return ((int)scene->box_count);
	else if (type == TYPE_CAPSULE)
		return ((int)scene->capsule_count);
	else
		return (0);
}

static void	add_items(t_build_item *items, size_t *k, int type, t_scene *scene)
{
	int	i;
	int	count;

	count = get_count_for_type(type, scene);
	if (count <= 0)
		return ;
	i = 0;
	while (i < count)
	{
		items[*k].ref.type = (uint8_t)type;
		items[*k].ref.index = (size_t)i;
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
	ft_print_debug("BVH Collect: spheres=%zu, planes=%zu, cylinders=%zu, ",
		scene->sphere_count, scene->plane_count, scene->cylinder_count);
	ft_print_debug("cones=%zu, meshes=%zu, anim=%zu\n",
		scene->cone_count, scene->mesh_count, scene->anim_count);
	add_items(items, &k, TYPE_SPHERE, scene);
	add_items(items, &k, TYPE_CYLINDER, scene);
	add_items(items, &k, TYPE_CONE, scene);
	add_items(items, &k, TYPE_TRI, scene);
	add_items(items, &k, TYPE_RECT, scene);
	add_items(items, &k, TYPE_PYRAMID, scene);
	add_items(items, &k, TYPE_BOX, scene);
	add_items(items, &k, TYPE_CAPSULE, scene);
	k = collect_complex(scene, items, k);
	ft_print_debug("BVH Collect Finished: total items=%zu\n", k);
	return (k);
}
