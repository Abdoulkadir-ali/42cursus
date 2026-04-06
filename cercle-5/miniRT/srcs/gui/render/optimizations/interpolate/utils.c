/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 10:16:43 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "optimizations.h"

size_t	blend_colors(t_vec2s c, double alpha)
{
	t_vec3i			rgb;
	t_vec3i			h;
	unsigned int	a;
	unsigned int	b;

	a = (unsigned int)(alpha * 256.0);
	b = 256 - a;
	rgb = rt_unpack_color_v(c.x);
	h = rt_unpack_color_v(c.y);
	rgb.x = (a * rgb.x + b * h.x) >> 8;
	rgb.y = (a * rgb.y + b * h.y) >> 8;
	rgb.z = (a * rgb.z + b * h.z) >> 8;
	return (rt_pack_color_v(rgb));
}

bool	depth_test(t_gui *gui, t_vec2i n, double cz)
{
	t_optimizations	*o;
	float			cur_d;

	o = &gui->opts;
	cur_d = o->depth_buf[n.y * gui->win.size.x + n.x];
	if (cur_d > 1e29f || (float)cz < 1e-4f)
		return (false);
	return (fabsf((float)cz - cur_d) / fmaxf((float)cz, cur_d) < DEPTH_THRESH);
}

t_transform	lerp_cam(t_optimizations *o, double alpha)
{
	t_transform	out;

	out.pos = vec3_lerp(o->prev_cam.pos, o->cur_cam.pos, alpha);
	out.forward = vec3_norm(vec3_lerp(o->prev_cam.forward,
				o->cur_cam.forward, alpha));
	out.right = vec3_norm(vec3_lerp(o->prev_cam.right,
				o->cur_cam.right, alpha));
	out.up = vec3_norm(vec3_lerp(o->prev_cam.up, o->cur_cam.up, alpha));
	return (out);
}

double	lerp_half(double a, double b, double t)
{
	return (a + (b - a) * t);
}
