/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/24 20:44:30 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

typedef bool (*t_intersect_fn)(const t_ray *, const void *, t_hit *);

static const t_intersect_fn g_intersect_dispatch[TYPE_MAX] = {
	[TYPE_SPHERE]       = (t_intersect_fn)intersect_sphere,
	[TYPE_PROXY_SPHERE] = (t_intersect_fn)intersect_sphere,
	[TYPE_PYRAMID]      = (t_intersect_fn)intersect_pyramid,
	[TYPE_BOX]          = (t_intersect_fn)intersect_box,
	[TYPE_CAPSULE]      = (t_intersect_fn)intersect_capsule,
	[TYPE_CYLINDER]     = (t_intersect_fn)intersect_cylinder,
	[TYPE_RECT]         = (t_intersect_fn)intersect_rect,
	[TYPE_CONE]         = (t_intersect_fn)intersect_cone,
	[TYPE_TRI]          = (t_intersect_fn)intersect_tri_shape,
	[TYPE_PLANE]        = (t_intersect_fn)intersect_plane,
	[TYPE_MESH]         = (t_intersect_fn)intersect_mesh,
	[TYPE_ANIM]         = (t_intersect_fn)intersect_mesh,
};

__attribute__((optimize("O3")))
static inline const void	*get_scene_object(t_scene *scene, t_bvh_ref ref)
{
	if (ref.type == TYPE_SPHERE || ref.type == TYPE_PROXY_SPHERE)
		return (&scene->spheres[ref.index]);
	if (ref.type == TYPE_PYRAMID) return (&scene->pyramids[ref.index]);
	if (ref.type == TYPE_BOX) return (&scene->boxes[ref.index]);
	if (ref.type == TYPE_CAPSULE) return (&scene->capsules[ref.index]);
	if (ref.type == TYPE_CYLINDER) return (&scene->cylinders[ref.index]);
	if (ref.type == TYPE_RECT) return (&scene->rects[ref.index]);
	if (ref.type == TYPE_CONE) return (&scene->cones[ref.index]);
	if (ref.type == TYPE_TRI) return (&scene->tris[ref.index]);
	if (ref.type == TYPE_PLANE) return (&scene->planes[ref.index]);
	if (ref.type == TYPE_MESH) return (&scene->meshes[ref.index]);
	if (ref.type == TYPE_ANIM) return (&scene->animated[ref.index].base);
	return (NULL);
}
__attribute__((optimize("O3")))bool	intersect_object(const t_ray *ray, t_scene *scene, t_bvh_ref ref,
			t_hit *hit)
{
	bool		res;
	const void	*obj;

	if (ref.type >= TYPE_MAX || !g_intersect_dispatch[ref.type])
		return (false);
	obj = get_scene_object(scene, ref);
	if (!obj)
		return (false);
	res = g_intersect_dispatch[ref.type](ray, obj, hit);
	if (res)
		hit->ref = ref;
	return (res);
}
