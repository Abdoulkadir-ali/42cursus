/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/15 00:00:00 by abdoali          ###   ########.fr       */
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

static bool	is_rounded_corner(t_panel p, int i, int j)
{
	int	dx;
	int	dy;
	int	r;

	r = PANEL_RADIUS;
	dx = 0;
	dy = 0;
	if (i < p.x + r && j < p.y + r)
	{
		dx = p.x + r - i;
		dy = p.y + r - j;
	}
	else if (i >= p.x + p.w - r && j < p.y + r)
	{
		dx = i - (p.x + p.w - r - 1);
		dy = p.y + r - j;
	}
	else if (i < p.x + r && j >= p.y + p.h - r)
	{
		dx = p.x + r - i;
		dy = j - (p.y + p.h - r - 1);
	}
	else if (i >= p.x + p.w - r && j >= p.y + p.h - r)
	{
		dx = i - (p.x + p.w - r - 1);
		dy = j - (p.y + p.h - r - 1);
	}
	return (dx * dx + dy * dy > r * r);
}

int	panel_color(t_panel panel, int i, int j)
{
	if (is_rounded_corner(panel, i, j))
		return (-1);
	if (i <= panel.x + 1 || i >= panel.x + panel.w - 2
		|| j <= panel.y + 1 || j >= panel.y + panel.h - 2)
		return (panel.brd);
	return (panel.bg);
}
