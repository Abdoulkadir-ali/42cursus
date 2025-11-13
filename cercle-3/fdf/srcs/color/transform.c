/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 18:24:11 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/13 01:57:37 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"

int	interpolate_color(int color1, int color2, double ratio)
{
	int	r1;
	int	g1;
	int	b1;
	int	r2;
	int	g2;
	int	b2;
	int	r;
	int	g;
	int	b;

	r1 = (color1 >> 16) & 0xFF;
	g1 = (color1 >> 8) & 0xFF;
	b1 = color1 & 0xFF;
	r2 = (color2 >> 16) & 0xFF;
	g2 = (color2 >> 8) & 0xFF;
	b2 = color2 & 0xFF;
	r = (int)(r1 * (1.0 - ratio) + r2 * ratio);
	g = (int)(g1 * (1.0 - ratio) + g2 * ratio);
	b = (int)(b1 * (1.0 - ratio) + b2 * ratio);
	r = clamp(r, 0, 255);
	g = clamp(g, 0, 255);
	b = clamp(b, 0, 255);
	return ((r << 16) | (g << 8) | b);
}

int	lerp(int c1, int c2, double t)
{
	return (interpolate_color(c1, c2, t));
}

int	shift_color(int color, int red_shift, int green_shift,  int blue_shift)
{
	int	r;
	int	g;
	int	b;

	r = ((color >> 16) & 0xFF) + red_shift;
	g = ((color >> 8) & 0xFF) + green_shift;
	b = (color & 0xFF) + blue_shift;
	r = clamp(r, 0, 255);
	g = clamp(g, 0, 255);
	b = clamp(b, 0, 255);
	return ((r << 16) | (g << 8) | b);
}
