/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 18:24:11 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/13 11:12:05 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"

double	clamp_d(double value, double min, double max)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);
	return (value);
}

unsigned int	shift_color(unsigned int color, int r_shift, int g_shift, int b_shift)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	r = get_red(color) + r_shift;
	g = get_green(color) + g_shift;
	b = get_blue(color) + b_shift;
	return (create_color(r, g, b));
}

unsigned int	interpolate_color(unsigned int c1, unsigned int c2, double ratio)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	r = get_red(c1) * (1.0 - ratio) + get_red(c2) * ratio;
	g = get_green(c1) * (1.0 - ratio) + get_green(c2) * ratio;
	b = get_blue(c1) * (1.0 - ratio) + get_blue(c2) * ratio;
	return (create_color(r, g, b));
}

unsigned int	get_height_color(double z, int min_z, int max_z)
{
	t_vec3	colors;
	double	ratio;
	double	shift;
	double	effective_z;
	double	max_effective;

	colors = create_vec3(0x0000FF, 0x00FF00, 0xFF0000);
	if (max_z == min_z)
		return (colors.y);
	shift = 0;
	if (min_z < 0)
		shift = -min_z;
	effective_z = z + shift;
	max_effective = max_z + shift;
	if (max_effective <= 0)
		return (colors.y);
	ratio = clamp_d(log(effective_z + 1) / log(max_effective + 1), 0.0, 1.0);
	if (ratio < 0.5)
		return (interpolate_color(colors.x, colors.y, ratio * 2.0));
	else
		return (interpolate_color(colors.y, colors.z, (ratio - 0.5) * 2.0));
}
