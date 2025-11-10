/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:14:05 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/10 15:21:12 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Extract RGB components
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

// Create color from RGB components
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

// Shift color based on red, blue, and green shifts
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
