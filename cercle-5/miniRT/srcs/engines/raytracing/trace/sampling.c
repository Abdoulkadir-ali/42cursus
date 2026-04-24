/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sampling.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/14 00:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

t_vec3	rt_random_cosine_weighted(t_vec3 normal, uint64_t *seed)
{
	double	r1;
	double	r2;
	double	r;
	double	phi;
	t_vec3	v[2];
	t_vec3	local;
	t_vec3	res;

	r1 = rt_rand_d(seed);
	r2 = rt_rand_d(seed);
	r = __builtin_sqrt(r1);
	phi = 2.0 * PI * r2;
	local.x = r * __builtin_cos(phi);
	local.y = r * __builtin_sin(phi);
	local.z = __builtin_sqrt(__builtin_fmax(0.0, 1.0 - r1));
	rt_build_onb(normal, &v[0], &v[1]);
	res = vec3_scale(v[0], local.x);
	res = vec3_add(res, vec3_scale(v[1], local.y));
	res = vec3_add(res, vec3_scale(normal, local.z));
	return (res);
}

void	rt_build_onb(t_vec3 n, t_vec3 *v1, t_vec3 *v2)
{
	t_vec3	up;

	if (__builtin_fabs(n.x) < 0.9)
		up = vec3(1, 0, 0);
	else
		up = vec3(0, 1, 0);
	*v1 = vec3_norm(vec3_cross(up, n));
	*v2 = vec3_cross(n, *v1);
}

static t_vec3	cone_to_world(t_vec3 axis, t_vec3 local, t_vec3 v1, t_vec3 v2)
{
	t_vec3	res;

	res = vec3_scale(axis, local.z);
	res = vec3_add(res, vec3_scale(v1, local.x));
	res = vec3_add(res, vec3_scale(v2, local.y));
	return (vec3_norm(res));
}

t_vec3	rt_random_on_cone(t_vec3 axis, double cos_theta_max, uint64_t *seed)
{
	double	cos_theta;
	double	phi;
	t_vec3	local;
	t_vec3	v[2];

	cos_theta = (1.0 - rt_rand_d(seed)) * (1.0 - cos_theta_max) + cos_theta_max;
	phi = rt_rand_d(seed) * 2.0 * PI;
	local.x = cos(phi) * sqrt(fmax(0.0, 1.0 - cos_theta * cos_theta));
	local.y = sin(phi) * sqrt(fmax(0.0, 1.0 - cos_theta * cos_theta));
	local.z = cos_theta;
	rt_build_onb(axis, &v[0], &v[1]);
	return (cone_to_world(axis, local, v[0], v[1]));
}
