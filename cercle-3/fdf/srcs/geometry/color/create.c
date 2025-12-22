/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:14:05 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/21 17:52:06 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry.h"

int	clamp(int value, int min, int max)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);
	return (value);
}

unsigned int	create_color(int r, int g, int b)
{
	int	rr;
	int	gg;
	int	bb;

	rr = clamp(r, 0, 255);
	gg = clamp(g, 0, 255);
	bb = clamp(b, 0, 255);
	return ((((unsigned int)rr) << 16) | (((unsigned int)gg) << 8) | ((unsigned int)bb));
}

unsigned int	create_color_rgb(t_vec3 rgb)
{
	return (create_color((int)rgb.x, (int)rgb.y, (int)rgb.z));
}

unsigned int	create_color_wrap(int r, int g, int b)
{
	return (create_color(r, g, b));
}
