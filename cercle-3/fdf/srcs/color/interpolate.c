/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpolate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:13:56 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/12 19:34:13 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"

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
