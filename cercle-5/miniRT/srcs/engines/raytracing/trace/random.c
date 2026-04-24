/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 23:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/14 07:10:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

/*
** Halton low-discrepancy sequence.
*/
double	rt_halton(size_t i, size_t base)
{
	double	f;
	double	r;

	f = 1.0;
	r = 0.0;
	while (i > 0)
	{
		f /= (double)base;
		r += f * (double)(i % base);
		i /= base;
	}
	return (r);
}

/*
** xorshift64* for high-quality, fast randomness.
** Eliminates banding artifacts seen with 32-bit LCG.
*/
uint64_t	rt_next_rand(uint64_t *seed)
{
	*seed ^= *seed >> 12;
	*seed ^= *seed << 25;
	*seed ^= *seed >> 27;
	return (*seed * 0x2545F4914F6CDD1DULL);
}

double	rt_rand_d(uint64_t *seed)
{
	return ((double)rt_next_rand(seed) / (double)0xFFFFFFFFFFFFFFFFULL);
}

/*
** Returns a random point on the surface of a unit sphere.
*/
t_vec3	rt_random_on_sphere(uint64_t *seed)
{
	double	phi;
	double	cos_theta;
	double	sin_theta;
	t_vec3	res;

	phi = 2.0 * PI * rt_rand_d(seed);
	cos_theta = 2.0 * rt_rand_d(seed) - 1.0;
	sin_theta = sqrt(1.0 - cos_theta * cos_theta);
	res.x = sin_theta * cos(phi);
	res.y = sin_theta * sin(phi);
	res.z = cos_theta;
	res.w = 0.0;
	return (res);
}

/*
** Returns a random point on the hemisphere facing 'normal'.
*/
t_vec3	rt_random_on_hemisphere(t_vec3 normal, uint64_t *seed)
{
	t_vec3	v;

	v = rt_random_on_sphere(seed);
	if (vec3_dot(v, normal) < 0.0)
		v = vec3_scale(v, -1.0);
	return (v);
}
