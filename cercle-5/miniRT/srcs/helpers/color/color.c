/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 10:52:37 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include <math.h>

/**
 * @brief Clips a color vector values to [0.0, 255.0].
 */
t_vec3	clip_color(t_vec3 color)
{
	color.x = fmin(fmax(color.x, 0.0), 255.0);
	color.y = fmin(fmax(color.y, 0.0), 255.0);
	color.z = fmin(fmax(color.z, 0.0), 255.0);
	return (color);
}

/**
 * @brief Converts a color from t_vec3 to t_vec3i (clamping included).
 */
t_vec3i	vec3_to_rgb(t_vec3 v)
{
	t_vec3i	rgb;

	v = clip_color(v);
	rgb.x = (int)v.x;
	rgb.y = (int)v.y;
	rgb.z = (int)v.z;
	rgb.w = 1;
	return (rgb);
}

/**
 * @brief Packs normalized [0.0, 1.0] OR [0.0, 255.0] RGB vector into an integer.
 * It detects if the input is [0,1] or [0,255] heuristically as per codebase
 * standards (if v.max > 1.0, assumed [0,255]).
 */
uint32_t	pack_rgb(t_vec3 v)
{
	uint32_t	r;
	uint32_t	g;
	uint32_t	b;

	if (v.x <= 1.0 && v.y <= 1.0 && v.z <= 1.0
		&& (v.x > 0.0 || v.y > 0.0 || v.z > 0.0))
	{
		v.x *= 255.0;
		v.y *= 255.0;
		v.z *= 255.0;
	}
	v = clip_color(v);
	r = (uint32_t)(uint8_t)v.x;
	g = (uint32_t)(uint8_t)v.y;
	b = (uint32_t)(uint8_t)v.z;
	return ((r << 16) | (g << 8) | b);
}

/**
 * @brief Packs a t_vec3i into a uint32_t.
 */
uint32_t	pack_rgb_v(t_vec3i v)
{
	uint32_t	r;
	uint32_t	g;
	uint32_t	b;

	r = (uint32_t)(uint8_t)v.x;
	g = (uint32_t)(uint8_t)v.y;
	b = (uint32_t)(uint8_t)v.z;
	return ((r << 16) | (g << 8) | b);
}
