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

__attribute__((optimize("O3")))
static t_vec3	aces_tonemap(t_vec3 x)
{
	t_vec3	abc;
	t_vec2	de;

	abc = vec3(2.51, 0.03, 2.43);
	de = vec2(0.59, 0.14);
	x.x = (x.x * (abc.x * x.x + abc.y)) / (x.x * (abc.z * x.x + de.x) + de.y);
	x.y = (x.y * (abc.x * x.y + abc.y)) / (x.y * (abc.z * x.y + de.x) + de.y);
	x.z = (x.z * (abc.x * x.z + abc.y)) / (x.z * (abc.z * x.z + de.x) + de.y);
	return (x);
}

__attribute__((optimize("O3")))
t_vec3	clamp_color(t_vec3 color, const t_raytracer_settings *opts)
{
	t_vec3	v;

	if (opts && opts->aces_enabled)
	{
		v = vec3_scale(color, 1.0 / 255.0);
		v = aces_tonemap(v);
		color = vec3_scale(v, 255.0);
	}
	color.x = color.x < 0.0 ? 0.0 : color.x > 255.0 ? 255.0 : color.x;
	color.y = color.y < 0.0 ? 0.0 : color.y > 255.0 ? 255.0 : color.y;
	color.z = color.z < 0.0 ? 0.0 : color.z > 255.0 ? 255.0 : color.z;
	return (color);
}

__attribute__((optimize("O3")))
t_vec3	pixel_color(t_vec3 obj, t_vec3 light, double intensity)
{
	t_vec3	f;

	f.x = obj.x * light.x * intensity / 255.0;
	f.y = obj.y * light.y * intensity / 255.0;
	f.z = obj.z * light.z * intensity / 255.0;
	return (f);
}
