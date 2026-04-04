/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 20:51:57 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

static bool	intersect_complex(const t_ray *ray, t_scene *scene, t_bvh_ref ref,
		t_hit *hit)
{
	if (ref.type == TYPE_RECT)
		return (intersect_rect(ray, &scene->rects[ref.index], hit));
	if (ref.type == TYPE_PYRAMID)
		return (intersect_pyramid(ray, &scene->pyramids[ref.index], hit));
	if (ref.type == TYPE_BOX)
		return (intersect_box(ray, &scene->boxes[ref.index], hit));
	if (ref.type == TYPE_CAPSULE)
		return (intersect_capsule(ray, &scene->capsules[ref.index], hit));
	if (ref.type == TYPE_MESH)
		return (intersect_mesh(ray, &scene->meshes[ref.index], hit));
	if (ref.type == TYPE_ANIM)
		return (intersect_mesh(ray, &scene->animated[ref.index].base, hit));
	return (false);
}

/*
** Dispatches ray intersection to the correct object type.
*/
bool	intersect_object(const t_ray *ray, t_scene *scene, t_bvh_ref ref,
		t_hit *hit)
{
	bool	res;

	res = false;
	if (ref.type == TYPE_SPHERE)
		res = intersect_sphere(ray, &scene->spheres[ref.index], hit);
	else if (ref.type == TYPE_PLANE)
		res = intersect_plane(ray, &scene->planes[ref.index], hit);
	else if (ref.type == TYPE_CYLINDER)
		res = intersect_cylinder(ray, &scene->cylinders[ref.index], hit);
	else if (ref.type == TYPE_CONE)
		res = intersect_cone(ray, &scene->cones[ref.index], hit);
	else if (ref.type == TYPE_TRI)
		res = intersect_tri_shape(ray, &scene->tris[ref.index], hit);
	else
		res = intersect_complex(ray, scene, ref, hit);
	if (res)
		hit->ref = ref;
	return (res);
}
