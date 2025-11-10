/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpolate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:13:56 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/10 15:13:59 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Interpolate between two colors based on a ratio (0.0 to 1.0)
int	interpolate_color(int color1, int color2, double ratio)
{
	int	r1;
	int	g1;
	int	b1;
	int	r2;
	int	g2;
	int	b2;

	r1 = get_red(color1);
	g1 = get_green(color1);
	b1 = get_blue(color1);
	r2 = get_red(color2);
	g2 = get_green(color2);
	b2 = get_blue(color2);
	return (create_color(
		r1 + (int)((r2 - r1) * ratio),
		g1 + (int)((g2 - g1) * ratio),
		b1 + (int)((b2 - b1) * ratio)
	));
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
