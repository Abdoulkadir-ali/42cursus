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
	unsigned int	a;
	unsigned int	ia;
	unsigned int	rb;
	unsigned int	g;

	a = (unsigned int)(alpha * 256.0f);
	ia = 256 - a;
	rb = (((unsigned int)src & 0xFF00FF) * a
		+ (dst & 0xFF00FF) * ia) >> 8;
	g = (((unsigned int)src & 0x00FF00) * a
		+ (dst & 0x00FF00) * ia) >> 8;
	return ((rb & 0xFF00FF) | (g & 0x00FF00));
}

static t_vec2i	corner_delta(t_panel p, t_vec2i pos)
{
	int		r;
	t_vec2i	d;

	r = PANEL_RADIUS;
	d = vec2i(0, 0);
	if (pos.x < p.box.pos.x + r && pos.y < p.box.pos.y + r)
		d = vec2i(p.box.pos.x + r - pos.x, p.box.pos.y + r - pos.y);
	else if (pos.x >= p.box.pos.x + p.box.size.x - r && pos.y < p.box.pos.y + r)
		d = vec2i(pos.x - (p.box.pos.x + p.box.size.x - r - 1), p.box.pos.y + r - pos.y);
	else if (pos.x < p.box.pos.x + r && pos.y >= p.box.pos.y + p.box.size.y - r)
		d = vec2i(p.box.pos.x + r - pos.x, pos.y - (p.box.pos.y + p.box.size.y - r - 1));
	else if (pos.x >= p.box.pos.x + p.box.size.x - r && pos.y >= p.box.pos.y + p.box.size.y - r)
		d = vec2i(pos.x - (p.box.pos.x + p.box.size.x - r - 1), pos.y - (p.box.pos.y + p.box.size.y - r - 1));
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
	if (i <= panel.box.pos.x + 1 || i >= panel.box.pos.x + panel.box.size.x - 2
		|| j <= panel.box.pos.y + 1 || j >= panel.box.pos.y + panel.box.size.y - 2)
		return (panel.brd);
	return (panel.bg);
}
