/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 18:24:11 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/13 02:37:55 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include <math.h>

int	shift_color(int color, int red_shift, int blue_shift, int green_shift)
{
	int	r;
	int	g;
	int	b;

	r = get_red(color) + red_shift;
	g = get_green(color) + green_shift;
	b = get_blue(color) + blue_shift;
	return (create_color(r, g, b));
}

int	interpolate_color(int c1, int c2, double ratio)
{
	int	r;
	int	g;
	int	b;

	r = get_red(c1) * (1.0 - ratio) + get_red(c2) * ratio;
	g = get_green(c1) * (1.0 - ratio) + get_green(c2) * ratio;
	b = get_blue(c1) * (1.0 - ratio) + get_blue(c2) * ratio;
	return (create_color(r, g, b));
}

int	get_height_color(double z, int min_z, int max_z)
{
	int color_low;
	int color_mid;
	int color_high;
	double ratio;
	double shift;
	double effective_z;
	double max_effective;

	color_low = 0x0000FF;
	color_mid = 0x00FF00;
	color_high = 0xFF0000;
	if (max_z == min_z)
		return (color_mid);
	shift = (min_z < 0) ? -min_z : 0;
	effective_z = z + shift;
	max_effective = max_z + shift;
	if (max_effective <= 0)
		return (color_mid);
	ratio = log(effective_z + 1) / log(max_effective + 1);
	if (ratio < 0)
		ratio = 0;
	if (ratio > 1)
		ratio = 1;
	if (ratio < 0.5)
		return (interpolate_color(color_low, color_mid, ratio * 2.0));
	else
		return (interpolate_color(color_mid, color_high, (ratio - 0.5) * 2.0));
}