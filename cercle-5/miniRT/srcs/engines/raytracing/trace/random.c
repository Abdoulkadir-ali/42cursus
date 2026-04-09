/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 23:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/09 23:50:00 by abdoali          ###   ########.fr       */
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
** Simple LCG for fast per-pixel/per-light randomness.
*/
uint32_t	rt_next_rand(uint32_t *seed)
{
	*seed = *seed * 1103515245 + 12345;
	return ((*seed / 65536) % 32768);
}

double	rt_rand_d(uint32_t *seed)
{
	return ((double)rt_next_rand(seed) / 32768.0);
}

/*
** Returns a random point on the surface of a unit sphere.
*/
t_vec3	rt_random_on_sphere(uint32_t *seed)
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
t_vec3	rt_random_on_hemisphere(t_vec3 normal, uint32_t *seed)
{
	t_vec3	v;

	v = rt_random_on_sphere(seed);
	if (vec3_dot(v, normal) < 0.0)
		v = vec3_scale(v, -1.0);
	return (v);
}

/*
** CIE color-space approximation for Kelvin temperature to RGB.
** Temperature range: 1000K to 40000K.
*/
t_vec3	rt_kelvin_to_rgb(double kelvin)
{
	t_vec3	rgb;
	double	tmp;

	kelvin /= 100.0;
	if (kelvin <= 66)
	{
		rgb.x = 255;
		rgb.y = 99.4708025861 * log(kelvin) - 161.1195681661;
		if (kelvin <= 19)
			rgb.z = 0;
		else
			rgb.z = 138.5177312231 * log(kelvin - 10) - 305.0447927307;
	}
	else
	{
		tmp = kelvin - 60;
		rgb.x = 329.698727446 * pow(tmp, -0.1332047592);
		rgb.y = 288.1221695283 * pow(tmp, -0.0755148492);
		rgb.z = 255;
	}
	rgb.x = clamp_d(rgb.x, 0, 255);
	rgb.y = clamp_d(rgb.y, 0, 255);
	rgb.z = clamp_d(rgb.z, 0, 255);
	rgb.w = 0;
	return (rgb);
}

/*
** Returns a random direction weighted by the cosine of the angle with 'normal'.
** Perfect for Lambertian (diffuse) GI bounces.
*/
t_vec3	rt_random_cosine_weighted(t_vec3 normal, uint32_t *seed)
{
	t_vec3	sphere_point;

	sphere_point = rt_random_on_sphere(seed);
	return (vec3_norm(vec3_add(normal, sphere_point)));
}

/*
** Builds an Orthogonal Normal Basis from a single normal vector.
*/
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

/*
** Samples a direction within a cone of half-angle 'theta_max' around 'axis'.
** Used for Solid Angle Importance Sampling of spherical lights.
*/
t_vec3	rt_random_on_cone(t_vec3 axis, double cos_theta_max, uint32_t *seed)
{
	double	cos_theta;
	double	sin_theta;
	double	phi;
	t_vec3	v;
	t_vec3	v1;
	t_vec3	v2;

	cos_theta = (1.0 - rt_rand_d(seed)) * (1.0 - cos_theta_max) + cos_theta_max;
	sin_theta = sqrt(fmax(0.0, 1.0 - cos_theta * cos_theta));
	phi = rt_rand_d(seed) * 2.0 * PI;
	v.x = cos(phi) * sin_theta;
	v.y = sin(phi) * sin_theta;
	v.z = cos_theta;
	rt_build_onb(axis, &v1, &v2);
	return (vec3_norm(vec3_add(vec3_scale(axis, v.z),
				vec3_add(vec3_scale(v1, v.x), vec3_scale(v2, v.y)))));
}
