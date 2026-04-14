/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blackbody.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/14 00:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

static void	rgb_lo_kelvin(double kelvin, t_vec3 *rgb)
{
	rgb->x = 255;
	rgb->y = 99.4708025861 * log(kelvin) - 161.1195681661;
	if (kelvin <= 19)
		rgb->z = 0;
	else
		rgb->z = 138.5177312231 * log(kelvin - 10) - 305.0447927307;
}

t_vec3	rt_kelvin_to_rgb(double kelvin)
{
	t_vec3	rgb;
	double	tmp;

	if (kelvin > 40000.0)
		kelvin = 40000.0;
	kelvin /= 100.0;
	if (kelvin <= 66)
		rgb_lo_kelvin(kelvin, &rgb);
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

void	apply_blackbody_to_mat(t_material *mat)
{
	t_vec3	bb;
	double	t_norm;

	if (mat->temperature <= 0.0)
	{
		mat->emission = vec3(0.0, 0.0, 0.0);
		mat->em_intensity = 1.0;
		return ;
	}
	bb = rt_kelvin_to_rgb(mat->temperature);
	mat->emission = bb;
	t_norm = mat->temperature / 6500.0;
	mat->em_intensity = fmin(t_norm * t_norm * 15000.0, 1e15);
}
