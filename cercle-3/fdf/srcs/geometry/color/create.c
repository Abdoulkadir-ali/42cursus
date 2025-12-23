/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:14:05 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/23 21:12:23 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry.h"

int	clamp(int value, int min, int max)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);
	return (value);
}

t_vec3	create_color(int r, int g, int b)
{
	t_vec3	color;

	color.x = clamp(r, 0, 255);
	color.y = clamp(g, 0, 255);
	color.z = clamp(b, 0, 255);
	return (color);
}

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

unsigned int	create_color_rgb(t_vec3 rgb)
{
	return (rgb_to_int(rgb));
}
