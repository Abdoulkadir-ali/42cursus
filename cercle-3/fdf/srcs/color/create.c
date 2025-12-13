/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:14:05 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/13 11:11:56 by abdoali          ###   ########.fr       */
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

int	create_color(int r, int g, int b)
{
	r = clamp(r, 0, 255);
	g = clamp(g, 0, 255);
	b = clamp(b, 0, 255);
	return ((r << 16) | (g << 8) | b);
}

int	create_color_rgb(t_vec3 rgb)
{
	return (create_color(rgb.x, rgb.y, rgb.z));
}

int	create_color_wrap(int r, int g, int b)
{
	unsigned int	rr;
	unsigned int	gg;
	unsigned int	bb;

	rr = (unsigned int)r & 0xFF;
	gg = (unsigned int)g & 0xFF;
	bb = (unsigned int)b & 0xFF;
	return ((rr << 16) | (gg << 8) | bb);
}
