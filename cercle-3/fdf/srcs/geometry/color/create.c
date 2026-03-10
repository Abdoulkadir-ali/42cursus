/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:14:05 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 03:36:44 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry.h"

/**
 * @brief Build an RGB color vector with channel clamping.
 * @param r Red channel value.
 * @param g Green channel value.
 * @param b Blue channel value.
 * @return Clamped RGB color vector.
 */
t_vec3	create_color(int r, int g, int b)
{
	t_vec3	color;

	color.x = clamp(r, 0, 255);
	color.y = clamp(g, 0, 255);
	color.z = clamp(b, 0, 255);
	return (color);
}

/**
 * @brief Convert an RGB vector into a packed integer color.
 * @param color RGB color vector.
 * @return Packed `0xRRGGBB` color value.
 */
unsigned int	rgb_to_int(t_vec3 color)
{
	int	r;
	int	g;
	int	b;

	r = (unsigned char)clamp(color.x, 0, 255);
	g = (unsigned char)clamp(color.y, 0, 255);
	b = (unsigned char)clamp(color.z, 0, 255);
	return ((r << 16) | (g << 8) | b);
}

/**
 * @brief Pack an RGB vector into an integer color.
 * @param rgb RGB color vector.
 * @return Packed `0xRRGGBB` color value.
 */
unsigned int	create_color_rgb(t_vec3 rgb)
{
	return (rgb_to_int(rgb));
}
