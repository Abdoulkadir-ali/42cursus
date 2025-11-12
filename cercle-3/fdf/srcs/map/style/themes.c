/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   themes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:14:21 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/12 17:13:47 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "map_style.h"

static int	get_gradient_color(int z, int min_z, int max_z)
{
	double	ratio;
	int		color_low;
	int		color_mid;
	int		color_high;
	int		r;
	int		g;
	int		b;

	color_low = 0x0000FF;
	color_mid = 0x00FF00;
	color_high = 0xFF0000;
	if (max_z == min_z)
		return (color_mid);
	ratio = (double)(z - min_z) / (double)(max_z - min_z);
	if (ratio < 0.5)
	{
		ratio = ratio * 2.0;
		r = (int)(((color_low >> 16) & 0xFF) * (1.0 - ratio) + ((color_mid >> 16) & 0xFF) * ratio);
		g = (int)(((color_low >> 8) & 0xFF) * (1.0 - ratio) + ((color_mid >> 8) & 0xFF) * ratio);
		b = (int)((color_low & 0xFF) * (1.0 - ratio) + (color_mid & 0xFF) * ratio);
	}
	else
	{
		ratio = (ratio - 0.5) * 2.0;
		r = (int)(((color_mid >> 16) & 0xFF) * (1.0 - ratio) + ((color_high >> 16) & 0xFF) * ratio);
		g = (int)(((color_mid >> 8) & 0xFF) * (1.0 - ratio) + ((color_high >> 8) & 0xFF) * ratio);
		b = (int)((color_mid & 0xFF) * (1.0 - ratio) + (color_high & 0xFF) * ratio);
	}
	return ((r << 16) | (g << 8) | b);
}

static int	get_solid_color(int z)
{
	if (z > 0)
		return (0xFF6B35);
	else if (z < 0)
		return (0x004E89);
	return (0xFFFFFF);
}

static int	get_zebra_color(int z)
{
	if (z % 2 == 0)
		return (0xFFFFFF);
	return (0x00FFFF);
}

static int	get_neon_color(int z)
{
	int	colors[5];
	int	index;

	colors[0] = 0xFF00FF;
	colors[1] = 0x00FFFF;
	colors[2] = 0xFFFF00;
	colors[3] = 0xFF0080;
	colors[4] = 0x00FF80;
	if (z < 0)
		z = -z;
	index = z % 5;
	return (colors[index]);
}

int	get_map_line_color(int z, int min_z, int max_z, t_map_style style)
{
	if (style == MAP_STYLE_GRADIENT)
		return (get_gradient_color(z, min_z, max_z));
	else if (style == MAP_STYLE_SOLID)
		return (get_solid_color(z));
	else if (style == MAP_STYLE_ZEBRA)
		return (get_zebra_color(z));
	else if (style == MAP_STYLE_NEON)
		return (get_neon_color(z));
	return (0xFFFFFF);
}
