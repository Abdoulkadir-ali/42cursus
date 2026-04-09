/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/13 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

static t_vec3	aces_tonemap(t_vec3 x)
{
	double	a = 2.51;
	double	b = 0.03;
	double	c = 2.43;
	double	d = 0.59;
	double	e = 0.14;

	x.x = (x.x * (a * x.x + b)) / (x.x * (c * x.x + d) + e);
	x.y = (x.y * (a * x.y + b)) / (x.y * (c * x.y + d) + e);
	x.z = (x.z * (a * x.z + b)) / (x.z * (c * x.z + d) + e);
	return (x);
}

t_vec3	clamp_color(t_vec3 color, const t_raytracer_settings *opts)
{
	t_vec3	v;

	v = vec3_scale(color, 1.0 / 255.0);
	if (!opts || opts->aces_enabled)
		v = aces_tonemap(v);
	color = vec3_scale(v, 255.0);
	color.x = fmin(fmax(color.x, 0.0), 255.0);
	color.y = fmin(fmax(color.y, 0.0), 255.0);
	color.z = fmin(fmax(color.z, 0.0), 255.0);
	return (color);
}

t_vec3	pixel_color(t_vec3 obj, t_vec3 light, double intensity)
{
	t_vec3	f;

	f.x = obj.x * light.x * intensity / 255.0;
	f.y = obj.y * light.y * intensity / 255.0;
	f.z = obj.z * light.z * intensity / 255.0;
	return (f);
}
