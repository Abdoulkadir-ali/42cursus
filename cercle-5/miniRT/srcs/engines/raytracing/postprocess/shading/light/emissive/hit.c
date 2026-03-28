/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 11:18:56 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

static double	light_att(double d_sq)
{
	return (1.0 / (1.0 + 0.1 * (d_sq)));
}

void	apply_emissive_hit(t_shading *sha, t_vec3 *total, t_material *m, t_vec3 lrad)
{
	t_vec3				light_dir;
	double				dist_to_light;
	double				ndotl;
	double				attenuation;
	const t_rt_engine	*rt;

	rt = sha->rt;
	if (vec3_mag_sq(sha->aux_v) > 250000.0)
		return ;
	dist_to_light = vec3_mag(sha->aux_v) - lrad.x - 0.001;
	light_dir = vec3_norm(sha->aux_v);
	if (is_in_shadow(rt->bvh, sha->hit->point, light_dir, dist_to_light))
		return ;
	ndotl = vec3_dot(sha->hit->normal, light_dir);
	if (ndotl <= 0.0)
		return ;
	attenuation = light_att(vec3_mag_sq(sha->aux_v));
	*total = vec3_add(*total, vec3_scale(m->emission, ndotl * attenuation));
}
