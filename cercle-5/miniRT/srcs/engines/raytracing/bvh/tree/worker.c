/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   worker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 14:38:50 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/04 12:45:00 by abdoali          ###   ########.fr       */
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

typedef struct s_add_task
{
	t_scene			*sc;
	t_build_item	*items;
	size_t			*k;
	int				type;
	size_t			next;
	size_t			start_k;
}	t_add_task;

static void	*add_worker(void *p)
{
	t_add_task	*t = p;
	size_t		i;
	size_t		ki;

	while (1)
	{
		i = __sync_fetch_and_add(&t->next, 1);
		if (i >= get_count_for_type(t->type, t->sc)) break ;
		ki = t->start_k + i;
		t->items[ki].ref.type = (uint8_t)t->type;
		t->items[ki].ref.index = i;
		t->items[ki].bbox = aabb_from_ref(t->sc, t->items[ki].ref);
		t->items[ki].centroid = get_centroid(&t->items[ki].bbox);
	}
	return (NULL);
}

static void	add_items_worker(t_build_item *it, size_t *k, int type, t_scene *sc)
{
	t_add_task	t;
	size_t		count;

	count = get_count_for_type(type, sc);
	if (count == 0)
		return ;
	t = (t_add_task){sc, it, k, type, 0, *k};
	parallel_run(sc->pool, count, add_worker, &t);
	*k += count;
}

static size_t	collect_complex(t_scene *scene, t_build_item *items, size_t k)
{
	add_items_worker(items, &k, TYPE_ANIM, scene);
	add_items_worker(items, &k, TYPE_MESH, scene);
	return (k);
}

size_t	collect_objects_worker(t_scene *scene, t_build_item *items)
{
	size_t	k;

	k = 0;
	ft_print_debug("BVH Collect: spheres=%zu, planes=%zu, cylinders=%zu, ",
		scene->sphere_count, scene->plane_count, scene->cylinder_count);
	ft_print_debug("cones=%zu, meshes=%zu, anim=%zu\n", scene->cone_count,
		scene->mesh_count, scene->anim_count);
	add_items_worker(items, &k, TYPE_SPHERE, scene);
	add_items_worker(items, &k, TYPE_CYLINDER, scene);
	add_items_worker(items, &k, TYPE_CONE, scene);
	add_items_worker(items, &k, TYPE_TRI, scene);
	add_items_worker(items, &k, TYPE_RECT, scene);
	add_items_worker(items, &k, TYPE_PYRAMID, scene);
	add_items_worker(items, &k, TYPE_BOX, scene);
	add_items_worker(items, &k, TYPE_CAPSULE, scene);
	/* Planes handled globally (trace_ray/is_in_shadow), not in BVH */
	k = collect_complex(scene, items, k);
	ft_print_debug("BVH Collect Finished: total items=%zu\n", k);
	return (k);
}
