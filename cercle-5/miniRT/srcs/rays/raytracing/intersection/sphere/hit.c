/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/13 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

/*
** Sets hit point, normal, UVs and tangent space for a sphere hit.
*/
void	set_sphere_hit_data(const t_ray *ray, t_sphere *sp, t_hit *hit)
{
	hit->point = vec3_add(ray->origin, vec3_scale(ray->direction, hit->t));
	hit->normal = vec3_scale(vec3_sub(hit->point, sp->transform.pos),
			1.0 / sqrt(sp->radius_sq));
	get_sphere_uv(hit->normal, &hit->u, &hit->v);
	vec3_orthonormal_basis(hit->normal, &hit->tangent, &hit->bitangent);
}
