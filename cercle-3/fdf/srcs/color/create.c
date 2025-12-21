/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:14:05 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/21 15:17:17 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"

int	clamp(int value, int min, int max)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);
	return (value);
}

unsigned int	create_color(unsigned char r, unsigned char g, unsigned char b)
{
	return (((unsigned int)r << 16) | ((unsigned int)g << 8) | (unsigned int)b);
}

unsigned int	create_color_rgb(t_vec3 rgb)
{
	return (create_color((unsigned char)rgb.x, (unsigned char)rgb.y, (unsigned char)rgb.z));
}

unsigned int	create_color_wrap(int r, int g, int b)
{
	return (create_color((unsigned char)r, (unsigned char)g, (unsigned char)b));
}

unsigned int	create_color_fast(int r, int g, int b)
{
	if (r < 0)
		r = 0;
	else if (r > 255)
		r = 255;
	if (g < 0)
		g = 0;
	else if (g > 255)
		g = 255;
	if (b < 0)
		b = 0;
	else if (b > 255)
		b = 255;
	return (((r & 0xFF) << 16) | ((g & 0xFF) << 8) | (b & 0xFF));
}

unsigned int	shift_color_fast(unsigned int c, int rs, int gs, int bs)
{
	int	r;
	int	g;
	int	b;

	r = (c >> 16) & 0xFF;
	g = (c >> 8) & 0xFF;
	b = c & 0xFF;
	r += rs;
	if (r < 0)
		r = 0;
	else if (r > 255)
		r = 255;
	g += gs;
	if (g < 0)
		g = 0;
	else if (g > 255)
		g = 255;
	b += bs;
	if (b < 0)
		b = 0;
	else if (b > 255)
		b = 255;
	return ((r << 16) | (g << 8) | b);
}
