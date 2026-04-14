/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   worker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 14:38:50 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/12 21:50:51 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

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

/*
** Worker thread for scene object collection.
** mark TYPE_PROXY_SPHERE: visible but no shadows for particles.
** skip radius_sq=0 spheres: degenerate nodes pollute BVH.
*/
static void	*add_worker(void *p)
{
	t_add_task	*t;
	size_t		i;
	size_t		ki;

	t = p;
	while (1)
	{
		i = __sync_fetch_and_add(&t->next, 1);
		if (i >= get_count_for_type(t->type, t->sc))
			break ;
		if (t->type == TYPE_SPHERE && t->sc->spheres[i].radius_sq <= 0.0)
			continue ;
		ki = t->start_k + __sync_fetch_and_add(&t->ki_next, 1);
		if (t->type == TYPE_SPHERE && i >= t->sc->proxy_sphere_base)
			t->items[ki].ref.type = (uint8_t)TYPE_PROXY_SPHERE;
		else
			t->items[ki].ref.type = (uint8_t)t->type;
		t->items[ki].ref.index = i;
		t->items[ki].bbox = aabb_from_ref(t->sc, t->items[ki].ref);
		t->items[ki].centroid = vec3_scale(vec3_add(t->items[ki].bbox.min,
					t->items[ki].bbox.max), 0.5);
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
	t = (t_add_task){sc, it, k, type, 0, *k, 0};
	parallel_run(sc->pool, count, add_worker, &t);
	*k += t.ki_next;
}

size_t	collect_objects_worker(t_scene *scene, t_build_item *items)
{
	size_t	k;

	k = 0;
	add_items_worker(items, &k, TYPE_PLANE, scene);
	add_items_worker(items, &k, TYPE_SPHERE, scene);
	add_items_worker(items, &k, TYPE_CYLINDER, scene);
	add_items_worker(items, &k, TYPE_CONE, scene);
	add_items_worker(items, &k, TYPE_TRI, scene);
	add_items_worker(items, &k, TYPE_RECT, scene);
	add_items_worker(items, &k, TYPE_PYRAMID, scene);
	add_items_worker(items, &k, TYPE_BOX, scene);
	add_items_worker(items, &k, TYPE_CAPSULE, scene);
	add_items_worker(items, &k, TYPE_ANIM, scene);
	add_items_worker(items, &k, TYPE_MESH, scene);
	return (k);
}
