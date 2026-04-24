/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   occlude_dispatch.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/12 21:50:51 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

static bool	occ_sphere(const t_ray *ray, t_sphere *sp, double max_t)
{
	t_vec3	oc;
	double	b;
	double	disc;
	double	t;
	double	sq;

	if (sp->radius_sq <= 0.0)
		return (false);
	oc = vec3_sub(ray->origin, sp->transform.pos);
	b = vec3_dot(oc, ray->direction);
	disc = b * b - (vec3_dot(oc, oc) - sp->radius_sq);
	if (disc < 0.0)
		return (false);
	sq = sqrt(disc);
	t = -b - sq;
	if (t < EPSILON)
		t = -b + sq;
	return (t > EPSILON && t < max_t);
}

typedef bool (*t_occlude_fn)(const t_ray *, const void *, double);

static const t_occlude_fn g_occlude_dispatch[TYPE_MAX] = {
	[TYPE_SPHERE]       = (t_occlude_fn)occ_sphere,
	[TYPE_PROXY_SPHERE] = NULL, /* Checked explicitly or implicitly handled */
	[TYPE_CYLINDER]     = (t_occlude_fn)occlude_cylinder,
	[TYPE_MESH]         = (t_occlude_fn)mesh_occluded,
	[TYPE_ANIM]         = (t_occlude_fn)mesh_occluded,
};

static inline const void	*get_occ_object(t_scene *sc, t_bvh_ref ref)
{
	if (ref.type == TYPE_SPHERE) return (&sc->spheres[ref.index]);
	if (ref.type == TYPE_CYLINDER) return (&sc->cylinders[ref.index]);
	if (ref.type == TYPE_MESH) return (&sc->meshes[ref.index]);
	if (ref.type == TYPE_ANIM) return (&sc->animated[ref.index].base);
	return (NULL);
}

/*
** Proxy spheres (particles) are tiny emissive glows -- skip shadow testing
** entirely to avoid 400+ sqrt calls per shadow ray.
*/
bool	occlude_primitive(const t_ray *ray, t_scene *sc, t_bvh_ref ref,
			double max_t)
{
	t_hit		h;
	const void	*obj;

	if (ref.type == TYPE_PROXY_SPHERE)
		return (false);
	if (ref.type < TYPE_MAX && g_occlude_dispatch[ref.type])
	{
		obj = get_occ_object(sc, ref);
		if (obj)
			return (g_occlude_dispatch[ref.type](ray, obj, max_t));
	}
	h.t = max_t;
	if (intersect_object(ray, sc, ref, &h))
		return (h.t < max_t);
	return (false);
}
