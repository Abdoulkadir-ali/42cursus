/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 14:38:50 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 14:38:50 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

static t_vec3	get_centroid(const t_aabb *bbox)
{
	t_vec3	sum;

	sum = vec3_add(bbox->min, bbox->max);
	return (vec3_scale(sum, 0.5));
}

static size_t	get_count_for_type(int type, t_scene *scene)
{
	if (type == TYPE_ANIM)
		return (scene->anim_count);
	if (type == TYPE_MESH)
		return (scene->mesh_count);
	if (type == TYPE_SPHERE)
		return (scene->sphere_count);
	if (type == TYPE_PLANE)
		return (scene->plane_count);
	if (type == TYPE_CYLINDER)
		return (scene->cylinder_count);
	if (type == TYPE_CONE)
		return (scene->cone_count);
	if (type == TYPE_TRI)
		return (scene->tri_count);
	if (type == TYPE_RECT)
		return (scene->rect_count);
	if (type == TYPE_PYRAMID)
		return (scene->pyramid_count);
	if (type == TYPE_BOX)
		return (scene->box_count);
	if (type == TYPE_CAPSULE)
		return (scene->capsule_count);
	return (0);
}

static void	add_items(t_build_item *items, size_t *k, int type, t_scene *scene)
{
	size_t	i;
	size_t	count;

	count = get_count_for_type(type, scene);
	if (count == 0)
		return ;
	i = 0;
	while (i < count)
	{
		items[*k].ref.type = (uint8_t)type;
		items[*k].ref.index = i++;
		items[*k].bbox = aabb_from_ref(scene, items[*k].ref);
		items[*k].centroid = get_centroid(&items[*k].bbox);
		(*k)++;
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
	ft_print_debug("cones=%zu, meshes=%zu, anim=%zu\n", scene->cone_count,
		scene->mesh_count, scene->anim_count);
	add_items(items, &k, TYPE_SPHERE, scene);
	add_items(items, &k, TYPE_CYLINDER, scene);
	add_items(items, &k, TYPE_CONE, scene);
	add_items(items, &k, TYPE_TRI, scene);
	add_items(items, &k, TYPE_RECT, scene);
	add_items(items, &k, TYPE_PYRAMID, scene);
	add_items(items, &k, TYPE_BOX, scene);
	add_items(items, &k, TYPE_CAPSULE, scene);
	add_items(items, &k, TYPE_PLANE, scene);
	k = collect_complex(scene, items, k);
	ft_print_debug("BVH Collect Finished: total items=%zu\n", k);
	return (k);
}
