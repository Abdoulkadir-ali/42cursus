/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 03:07:24 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 06:40:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

static size_t	add_extra_to_list(t_scene *sc, t_build_item *it, int n)
{
	int	i;

	i = -1;
	while (++i < sc->tri_count)
		it[n++] = (t_build_item){(t_prim_ref){TYPE_TRI, i},
			tri_aabb(&sc->triangles[i]), sc->triangles[i].transform.pos};
	i = -1;
	while (++i < sc->rect_count)
		it[n++] = (t_build_item){(t_prim_ref){TYPE_RECT, i},
			rect_aabb(&sc->rects[i]), sc->rects[i].transform.pos};
	i = -1;
	while (++i < sc->pyramid_count)
		it[n++] = (t_build_item){(t_prim_ref){TYPE_PYRAMID, i},
			pyramid_aabb(&sc->pyramids[i]), sc->pyramids[i].transform.pos};
	i = -1;
	while (++i < sc->box_count)
		it[n++] = (t_build_item){(t_prim_ref){TYPE_BOX, i},
			box_aabb(&sc->boxes[i]), sc->boxes[i].transform.pos};
	i = -1;
	while (++i < sc->capsule_count)
		it[n++] = (t_build_item){(t_prim_ref){TYPE_CAPSULE, i},
			capsule_aabb(&sc->capsules[i]), sc->capsules[i].transform.pos};
	return (n);
}

/**
 * @brief Traverses the entire scene and identifies all buildable objects, 
 * calculating their individual AABBs and centroids for BVH sorting.
 */
size_t	collect_objects(t_scene *scene, t_build_item *items)
{
	size_t	n;

	n = -1;
	while (++n < (size_t)scene->sphere_count)
		items[n] = (t_build_item){(t_prim_ref){TYPE_SPHERE, (int)n},
			sphere_aabb(&scene->spheres[n]), scene->spheres[n].transform.pos};
	n = (size_t)scene->sphere_count - 1;
	int i = -1;
	while (++i < scene->plane_count)
		items[++n] = (t_build_item){(t_prim_ref){TYPE_PLANE, i},
			plane_aabb(&scene->planes[i]), scene->planes[i].transform.pos};
	i = -1;
	while (++i < scene->cylinder_count)
		items[++n] = (t_build_item){(t_prim_ref){TYPE_CYLINDER, i},
			cylinder_aabb(&scene->cylinders[i]), scene->cylinders[i].transform.pos};
	i = -1;
	while (++i < scene->cone_count)
		items[++n] = (t_build_item){(t_prim_ref){TYPE_CONE, i},
			cone_aabb(&scene->cones[i]), scene->cones[i].transform.pos};
	return (add_extra_to_list(scene, items, (int)n + 1));
}
