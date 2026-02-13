/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   overlay.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 00:00:00 by antigravity       #+#    #+#             */
/*   Updated: 2026/02/11 20:30:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

/*
** Blends two colors with alpha.
*/
unsigned int	color_blend(unsigned int dst, int src, float alpha)
{
	int	r;
	int	g;
	int	b;

	r = ((src >> 16) & 0xFF) * alpha + ((dst >> 16) & 0xFF) * (1.0 - alpha);
	g = ((src >> 8) & 0xFF) * alpha + ((dst >> 8) & 0xFF) * (1.0 - alpha);
	b = (src & 0xFF) * alpha + (dst & 0xFF) * (1.0 - alpha);
	return ((r << 16) | (g << 8) | b);
}

int	panel_color(t_panel panel, int i, int j)
{
	if (i == panel.x || i == panel.x + panel.w - 1 || j == panel.y
		|| j == panel.y + panel.h - 1)
		return (panel.brd);
	return (panel.bg);
}
