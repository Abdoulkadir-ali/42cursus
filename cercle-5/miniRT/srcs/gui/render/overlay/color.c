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

#include "render.h"

/*
** Blends two colors with alpha.
*/
unsigned int	color_blend(unsigned int dst, int src, float alpha)
{
	t_vec3i	rgb;

	rgb.x = ((src >> 16) & 0xFF) * alpha + ((dst >> 16) & 0xFF) * (1.0 - alpha);
	rgb.y = ((src >> 8) & 0xFF) * alpha + ((dst >> 8) & 0xFF) * (1.0 - alpha);
	rgb.z = (src & 0xFF) * alpha + (dst & 0xFF) * (1.0 - alpha);
	return ((rgb.x << 16) | (rgb.y << 8) | rgb.z);
}

static t_vec2i	corner_delta(t_panel p, t_vec2i pos)
{
	int		r;
	t_vec2i	d;

	r = PANEL_RADIUS;
	d = vec2i(0, 0);
	if (pos.x < p.x + r && pos.y < p.y + r)
		d = vec2i(p.x + r - pos.x, p.y + r - pos.y);
	else if (pos.x >= p.x + p.w - r && pos.y < p.y + r)
		d = vec2i(pos.x - (p.x + p.w - r - 1), p.y + r - pos.y);
	else if (pos.x < p.x + r && pos.y >= p.y + p.h - r)
		d = vec2i(p.x + r - pos.x, pos.y - (p.y + p.h - r - 1));
	else if (pos.x >= p.x + p.w - r && pos.y >= p.y + p.h - r)
		d = vec2i(pos.x - (p.x + p.w - r - 1), pos.y - (p.y + p.h - r - 1));
	return (d);
}

static bool	is_rounded_corner(t_panel p, int i, int j)
{
	int		r;
	t_vec2i	d;

	r = PANEL_RADIUS;
	d = corner_delta(p, vec2i(i, j));
	return (d.x * d.x + d.y * d.y > r * r);
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
