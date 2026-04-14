/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/12 21:50:51 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

/*
** Dispatches ray intersection — flattened, most-frequent types first.
*/
static bool	intersect_dispatch_ext(const t_ray *ray, t_scene *sc, t_bvh_ref ref,
				t_hit *hit)
{
	if (ref.type == TYPE_CONE)
		return (intersect_cone(ray, &sc->cones[ref.index], hit));
	if (ref.type == TYPE_TRI)
		return (intersect_tri_shape(ray, &sc->tris[ref.index], hit));
	if (ref.type == TYPE_PLANE)
		return (intersect_plane(ray, &sc->planes[ref.index], hit));
	if (ref.type == TYPE_MESH)
		return (intersect_mesh(ray, &sc->meshes[ref.index], hit));
	if (ref.type == TYPE_ANIM)
		return (intersect_mesh(ray, &sc->animated[ref.index].base, hit));
	return (false);
}

bool	intersect_object(const t_ray *ray, t_scene *scene, t_bvh_ref ref,
		t_hit *hit)
{
	bool	res;

	res = false;
	if (ref.type == TYPE_SPHERE || ref.type == TYPE_PROXY_SPHERE)
		res = intersect_sphere(ray, &scene->spheres[ref.index], hit);
	else if (ref.type == TYPE_PYRAMID)
		res = intersect_pyramid(ray, &scene->pyramids[ref.index], hit);
	else if (ref.type == TYPE_BOX)
		res = intersect_box(ray, &scene->boxes[ref.index], hit);
	else if (ref.type == TYPE_CAPSULE)
		res = intersect_capsule(ray, &scene->capsules[ref.index], hit);
	else if (ref.type == TYPE_CYLINDER)
		res = intersect_cylinder(ray, &scene->cylinders[ref.index], hit);
	else if (ref.type == TYPE_RECT)
		res = intersect_rect(ray, &scene->rects[ref.index], hit);
	else
		res = intersect_dispatch_ext(ray, scene, ref, hit);
	if (res)
		hit->ref = ref;
	return (res);
}
