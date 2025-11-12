/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lerp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 18:24:11 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/12 18:24:19 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"

int	lerp_color(int c1, int c2, double t)
{
	int r1;
	int g1;
	int b1;
	int r2;
	int g2;
	int b2;
	int r;
	int g;
	int b;

	r1 = (c1 >> 16) & 0xFF;
	g1 = (c1 >> 8) & 0xFF;
	b1 = c1 & 0xFF;
	r2 = (c2 >> 16) & 0xFF;
	g2 = (c2 >> 8) & 0xFF;
	b2 = c2 & 0xFF;
	r = (int)(r1 + (r2 - r1) * t);
	g = (int)(g1 + (g2 - g1) * t);
	b = (int)(b1 + (b2 - b1) * t);
	return ((r << 16) | (g << 8) | b);
}