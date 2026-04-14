/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bloom.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/12 05:40:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "optimizations.h"
#include <math.h>

static void	bright_pass(t_gui *gui)
{
	t_vec3f		c;
	size_t		i;
	float		t;
	float		s;

	t = (float)gui->rt_engine.settings.bloom_threshold;
	s = fmaxf(255.0f - t, 1.0f);
	i = -1;
	while (++i < (size_t)gui->win.disp_size.x * (size_t)gui->win.disp_size.y)
	{
		c = rt_unpack_color(((uint32_t *)gui->win.disp_addrs
				[gui->render.back_idx])[i]);
		t = c.x * 0.299f + c.y * 0.587f + c.z * 0.114f;
		if (t > (float)gui->rt_engine.settings.bloom_threshold)
		{
			c.x *= (t - gui->rt_engine.settings.bloom_threshold) / s;
			c.y *= (t - gui->rt_engine.settings.bloom_threshold) / s;
			c.z *= (t - gui->rt_engine.settings.bloom_threshold) / s;
		}
		else
			c = (t_vec3f){0.0f, 0.0f, 0.0f, 0.0f};
		gui->opts.bloom_buf[i] = rt_pack_color(c);
	}
}

static t_vec3f	sample_blur(t_gui *gui, t_vec2s p, t_vec2i st, uint32_t *s)
{
	t_vec3f	acc;
	int		k;
	long	o;

	acc = (t_vec3f){0, 0, 0, 0};
	k = -5;
	while (++k < 4)
	{
		o = (long)p.y + k * (long)st.x * (st.y != 0);
		if (o >= 0 && o < (long)gui->win.disp_size.y && !((st.y == 0)
				&& ((long)p.x + k * (long)st.x < 0 || (long)p.x + k * (long)st.x
					>= (long)gui->win.disp_size.x)))
		{
			acc = vec3f_add(acc, rt_unpack_color(s[p.y * gui->win.disp_size.x
						+ p.x + k * st.x * (gui->win.disp_size.x * (st.y != 0)
							+ (st.y == 0))]));
		}
	}
	acc.x /= 9.0f;
	acc.y /= 9.0f;
	acc.z /= 9.0f;
	return (acc);
}

static void	blur_axis(t_gui *gui, size_t step, bool vert)
{
	t_vec2s		p;
	uint32_t	*s;
	uint32_t	*d;
	t_vec3f		acc;

	s = (uint32_t *[]){gui->opts.bloom_buf, gui->opts.bloom_tmp}[vert];
	d = (uint32_t *[]){gui->opts.bloom_tmp, gui->opts.bloom_buf}[vert];
	p.y = 0;
	while (p.y < (size_t)gui->win.disp_size.y)
	{
		p.x = 0;
		while (p.x < (size_t)gui->win.disp_size.x)
		{
			acc = sample_blur(gui, p, (t_vec2i){(int)step, (int)vert}, s);
			d[p.y * (size_t)gui->win.disp_size.x + p.x] = rt_pack_color(acc);
			p.x++;
		}
		p.y++;
	}
}

static void	blend_bloom(t_gui *gui)
{
	t_vec3f		b;
	t_vec3f		g;
	size_t		i;
	uint32_t	*src;

	src = (uint32_t *)gui->win.disp_addrs[gui->render.back_idx];
	i = -1;
	while (++i < (size_t)gui->win.disp_size.x * (size_t)gui->win.disp_size.y)
	{
		b = rt_unpack_color(src[i]);
		g = rt_unpack_color(gui->opts.bloom_buf[i]);
		b.x = b.x + g.x * gui->rt_engine.settings.bloom_intensity;
		b.y = b.y + g.y * gui->rt_engine.settings.bloom_intensity;
		b.z = b.z + g.z * gui->rt_engine.settings.bloom_intensity;
		b.x = fminf(b.x, 255.f);
		b.y = fminf(b.y, 255.f);
		b.z = fminf(b.z, 255.f);
		src[i] = rt_pack_color(b);
	}
}

void	bloom_frame(t_gui *gui)
{
	size_t	ss;
	int		p;
	int		i;

	if (!gui->opts.bloom_buf || !gui->opts.bloom_tmp || !gui->win.addr)
		return ;
	ss = (size_t)fmaxf(1.0f, (float)gui->rt_engine.settings.bloom_radius
			* fmaxf((float)gui->rt_engine.settings.bloom_intensity, 0.01f));
	p = (int)fmaxf(1.0f, (float)gui->rt_engine.settings.bloom_radius);
	bright_pass(gui);
	i = -1;
	while (++i < p)
	{
		blur_axis(gui, ss, false);
		blur_axis(gui, ss, true);
	}
	blend_bloom(gui);
}
