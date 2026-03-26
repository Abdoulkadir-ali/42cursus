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

static size_t	add_prim_to_list(t_scene *sc, t_build_item *it, int n)
{
	int	i;

	i = -1;
	while (++i < sc->sphere_count)
		it[n++] = (t_build_item){(t_bvh_ref){TYPE_SPHERE, i},
			sphere_aabb(&sc->spheres[i]), sc->spheres[i].transform.pos};
	i = -1;
	while (++i < sc->plane_count)
		it[n++] = (t_build_item){(t_bvh_ref){TYPE_PLANE, i},
			plane_aabb(&sc->planes[i]), sc->planes[i].transform.pos};
	i = -1;
	while (++i < sc->cylinder_count)
		it[n++] = (t_build_item){(t_bvh_ref){TYPE_CYLINDER, i},
			cylinder_aabb(&sc->cylinders[i]), sc->cylinders[i].transform.pos};
	i = -1;
	while (++i < sc->cone_count)
		it[n++] = (t_build_item){(t_bvh_ref){TYPE_CONE, i},
			cone_aabb(&sc->cones[i]), sc->cones[i].transform.pos};
	return (n);
}

static size_t	add_extra_to_list(t_scene *sc, t_build_item *it, int n)
{
	int	i;

	i = -1;
	while (++i < sc->tri_count)
		it[n++] = (t_build_item){(t_bvh_ref){TYPE_TRI, i},
			tri_shape_aabb(&sc->tris[i]), sc->tris[i].transform.pos};
	i = -1;
	while (++i < sc->rect_count)
		it[n++] = (t_build_item){(t_bvh_ref){TYPE_RECT, i},
			rect_aabb(&sc->rects[i]), sc->rects[i].transform.pos};
	i = -1;
	while (++i < sc->pyramid_count)
		it[n++] = (t_build_item){(t_bvh_ref){TYPE_PYRAMID, i},
			pyramid_aabb(&sc->pyramids[i]), sc->pyramids[i].transform.pos};
	i = -1;
	while (++i < sc->box_count)
		it[n++] = (t_build_item){(t_bvh_ref){TYPE_BOX, i},
			box_aabb(&sc->boxes[i]), sc->boxes[i].transform.pos};
	i = -1;
	while (++i < sc->capsule_count)
		it[n++] = (t_build_item){(t_bvh_ref){TYPE_CAPSULE, i},
			capsule_aabb(&sc->capsules[i]), sc->capsules[i].transform.pos};
	return (n);
}

static size_t	add_mesh_to_list(t_scene *sc, t_build_item *it, int n)
{
	int	i;

	i = -1;
	while (++i < sc->mesh_count)
		it[n++] = (t_build_item){(t_bvh_ref){TYPE_MESH, i},
			sc->meshes[i].bbox, sc->meshes[i].transform.pos};
	i = -1;
	while (++i < sc->anim_count)
		it[n++] = (t_build_item){(t_bvh_ref){TYPE_ANIM, i},
			sc->animated[i].base.bbox, sc->animated[i].base.transform.pos};
	return (n);
}

/**
 * @brief Traverses the entire scene and identifies all buildable objects, 
 * calculating their individual AABBs and centroids for BVH sorting.
 */
size_t	collect_objects(t_scene *scene, t_build_item *items)
{
	size_t	n;

	n = add_prim_to_list(scene, items, 0);
	n = add_extra_to_list(scene, items, n);
	return (add_mesh_to_list(scene, items, n));
}
