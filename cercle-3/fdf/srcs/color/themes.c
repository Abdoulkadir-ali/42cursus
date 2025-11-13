/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   themes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/13 01:45:53 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"

int	get_height_color(int z, int min_z, int max_z)
{
	int	color_low;
	int	color_mid;
	int	color_high;
	double	ratio;

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
