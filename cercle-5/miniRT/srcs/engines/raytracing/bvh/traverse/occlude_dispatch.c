/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   occlude_dispatch.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/04 20:15:31 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

static bool	occ_sphere(const t_ray *ray, t_sphere *sp, double max_t)
{
	t_vec3	oc;
	double	b;
	double	disc;
	double	t;

	oc = vec3_sub(ray->origin, sp->transform.pos);
	b = vec3_dot(oc, ray->direction);
	disc = b * b - (vec3_dot(oc, oc) - sp->radius_sq);
	if (disc < 0.0)
		return (false);
	t = -b - sqrt(disc);
	if (t < EPSILON)
		t = -b + sqrt(disc);
	return (t > EPSILON && t < max_t);
}

bool	occlude_primitive(const t_ray *ray, t_scene *sc, t_bvh_ref ref,
		double max_t)
{
	t_hit	h;

	if (ref.type == TYPE_SPHERE)
		return (occ_sphere(ray, &sc->spheres[ref.index], max_t));
	if (ref.type == TYPE_CYLINDER)
		return (occlude_cylinder(ray, &sc->cylinders[ref.index], max_t));
	if (ref.type == TYPE_MESH)
		return (mesh_occluded(ray, &sc->meshes[ref.index], max_t));
	if (ref.type == TYPE_ANIM)
		return (mesh_occluded(ray, &sc->animated[ref.index].base, max_t));
	h.t = max_t;
	if (intersect_object(ray, sc, ref, &h))
		return (h.t < max_t);
	return (false);
}
