/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/24 20:18:12 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

/*
** Blends two colors with alpha.
*/
unsigned int	color_blend(unsigned int dst, int src, float alpha)
{
	t_vec3i	rgb;
	float	inv_alpha;

	inv_alpha = 1.0f - alpha;
	rgb.x = ((src >> 16) & 0xFF) * alpha + ((dst >> 16) & 0xFF) * inv_alpha;
	rgb.y = ((src >> 8) & 0xFF) * alpha + ((dst >> 8) & 0xFF) * inv_alpha;
	rgb.z = (src & 0xFF) * alpha + (dst & 0xFF) * inv_alpha;
	return ((rgb.x << 16) | (rgb.y << 8) | rgb.z);
}

static t_vec2i	corner_delta(t_panel p, t_vec2i pos)
{
	int		r;
	int		sz_x;
	int		sz_y;
	t_vec2i	d;

	r = PANEL_RADIUS;
	sz_x = p.size.x;
	sz_y = p.size.y;
	d = vec2i(0, 0);
	if (pos.x < p.pos.x + r && pos.y < p.pos.y + r)
		d = vec2i(p.pos.x + r - pos.x, p.pos.y + r - pos.y);
	else if (pos.x >= p.pos.x + sz_x - r && pos.y < p.pos.y + r)
		d = vec2i(pos.x - (p.pos.x + sz_x - r - 1), p.pos.y + r - pos.y);
	else if (pos.x < p.pos.x + r && pos.y >= p.pos.y + sz_y - r)
		d = vec2i(p.pos.x + r - pos.x, pos.y - (p.pos.y + sz_y - r - 1));
	else if (pos.x >= p.pos.x + sz_x - r && pos.y >= p.pos.y + sz_y - r)
		d = vec2i(pos.x - (p.pos.x + sz_x - r - 1), pos.y - (p.pos.y
					+ sz_y - r - 1));
	return (d);
}

static bool	is_rounded_corner(t_panel p, t_vec2i pos)
{
	int		r;
	t_vec2i	d;

	r = PANEL_RADIUS;
	d = corner_delta(p, pos);
	return (d.x * d.x + d.y * d.y > r * r);
}

int	panel_color(t_panel panel, t_vec2i pos)
{
	int	sz_x;
	int	sz_y;

	if (is_rounded_corner(panel, pos))
		return (-1);
	sz_x = panel.size.x;
	sz_y = panel.size.y;
	if (pos.x <= panel.pos.x + 1 || pos.x >= panel.pos.x + sz_x - 2
		|| pos.y <= panel.pos.y + 1 || pos.y >= panel.pos.y + sz_y - 2)
		return (panel.brd);
	return (panel.bg);
}
