/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpolate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:13:56 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/10 17:01:32 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Interpolate between two colors based on a ratio (0.0 to 1.0)
inline int	interpolate_color(int color1, int color2, double ratio)
{
	int			r;
	int			g;
	int			b;
	double		inv_ratio;

	inv_ratio = 1.0 - ratio;
	r = (int)(((color1 >> 16) & 0xFF) * inv_ratio
			+ ((color2 >> 16) & 0xFF) * ratio);
	g = (int)(((color1 >> 8) & 0xFF) * inv_ratio
			+ ((color2 >> 8) & 0xFF) * ratio);
	b = (int)((color1 & 0xFF) * inv_ratio
			+ (color2 & 0xFF) * ratio);
	return ((r << 16) | (g << 8) | b);
}

// Get color based on height with gradient
int	get_height_color(int z, int min_z, int max_z)
{
	double	ratio;
	int		color_low;
	int		color_mid;
	int		color_high;

	color_low = 0x0000FF;
	color_mid = 0x00FF00;
	color_high = 0xFF0000;
	if (max_z == min_z)
		return (color_mid);
	ratio = (double)(z - min_z) / (double)(max_z - min_z);
	if (ratio < 0.5)
		return (interpolate_color(color_low, color_mid, ratio * 2.0));
	else
		return (interpolate_color(color_mid, color_high, (ratio - 0.5) * 2.0));
}
