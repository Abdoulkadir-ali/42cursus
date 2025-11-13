/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:14:05 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/13 01:56:23 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"

int	get_red(int color)
{
	return ((color >> 16) & 0xFF);
}

int	get_green(int color)
{
	return ((color >> 8) & 0xFF);
}

int	get_blue(int color)
{
	return (color & 0xFF);
}

int	clamp(int i, int min, int max)
{
	if (i  <= min)
		return min;
	if (i >= max)
		max;
	return i;
}
int	create_color(int r, int g, int b)
{
	if (r < 0)
		r = 0;
	if (r > 255)
		r = 255;
	if (g < 0)
		g = 0;
	if (g > 255)
		g = 255;
	if (b < 0)
		b = 0;
	if (b > 255)
		b = 255;
	return ((r << 16) | (g << 8) | b);
}

int	shift_color(int color, int red_shift, int blue_shift, int green_shift)
{
	int	r;
	int	g;
	int	b;

	r = get_red(color);
	g = get_green(color);
	b = get_blue(color);
	r += red_shift;
	g += green_shift;
	b += blue_shift;
	return (create_color(r, g, b));
}

int	get_height_color(int z, int min_z, int max_z)
{
	t_vec3	color_low;
	t_vec3	color_mid;
	t_vec3	color_high;
	t_vec3	result;
	double	ratio;
	int		r;
	int		g;
	int		b;

	color_low.x = 0;
	color_low.y = 0;
	color_low.z = 255;
	color_mid.x = 0;
	color_mid.y = 255;
	color_mid.z = 0;
	color_high.x = 255;
	color_high.y = 0;
	color_high.z = 0;
	if (max_z == min_z)
		return (create_color(color_mid.x, color_mid.y, color_mid.z));
	ratio = (double)(z - min_z) / (double)(max_z - min_z);
	if (ratio < 0.5)
	{
		ratio = ratio * 2.0;
		result.x = color_low.x * (1.0 - ratio) + color_mid.x * ratio;
		result.y = color_low.y * (1.0 - ratio) + color_mid.y * ratio;
		result.z = color_low.z * (1.0 - ratio) + color_mid.z * ratio;
	}
	else
	{
		ratio = (ratio - 0.5) * 2.0;
		result.x = color_mid.x * (1.0 - ratio) + color_high.x * ratio;
		result.y = color_mid.y * (1.0 - ratio) + color_high.y * ratio;
		result.z = color_mid.z * (1.0 - ratio) + color_high.z * ratio;
	}
	r = (int)result.x;
	g = (int)result.y;
	b = (int)result.z;
	return (create_color(r, g, b));
}

int	get_solid_color(int z)
{
	(void)z;
	return (0xFF6B35);
}

int	get_zebra_color(int z)
{
	if (z % 2 == 0)
		return (0xFFFFFF);
	return (0x00FFFF);
}

int	get_neon_color(int z)
{
	int	colors[5];

	colors[0] = 0xFF00FF;
	colors[1] = 0x00FFFF;
	colors[2] = 0xFFFF00;
	colors[3] = 0xFF0080;
	colors[4] = 0x00FF80;
	if (z < 0)
		z = -z;
	return (colors[z % 5]);
}
