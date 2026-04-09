/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bloom.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/09 23:11:54 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "optimizations.h"
#include <math.h>

static float
bloom_luminance(t_vec3f color)
{
	return (color.x * 0.299f + color.y * 0.587f + color.z * 0.114f);
}

static void
bright_pass(t_gui *gui)
{
	t_optimizations	*o;
	uint32_t	*disp;
	t_vec3f		color;
	size_t		width;
	size_t		height;
	size_t		n;
	size_t		i;
	float		threshold;
	float		scale;

	o = &gui->opts;
	disp = (uint32_t *)gui->win.addr;
	width = gui->win.disp_size.x;
	height = gui->win.disp_size.y;
	n = width * height;
	threshold = (float)gui->rt_engine.settings.bloom_threshold;
	scale = fmaxf(255.0f - threshold, 1.0f);
	i = 0;
	while (i < n)
	{
		color = rt_unpack_color(disp[i]);
		if (bloom_luminance(color) > threshold)
		{
			float factor = (bloom_luminance(color) - threshold) / scale;
			color.x *= factor;
			color.y *= factor;
			color.z *= factor;
		}
		else
		{
			color.x = 0.0f;
			color.y = 0.0f;
			color.z = 0.0f;
		}
		o->bloom_buf[i] = rt_pack_color(color);
		i++;
	}
}

static void
blur_horizontal(t_gui *gui, size_t step)
{
	t_optimizations	*o;
	uint32_t	*src;
	uint32_t	*dst;
	t_vec3f		acc;
	t_vec3f		color;
	size_t		width;
	size_t		height;
	size_t		x;
	size_t		y;
	size_t		count;
	size_t		off;

	o = &gui->opts;
	src = o->bloom_buf;
	dst = o->bloom_tmp;
	width = gui->win.disp_size.x;
	height = gui->win.disp_size.y;
	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			acc = (t_vec3f){0.0f, 0.0f, 0.0f, 0.0f};
			count = 0;
			off = (y * width + x);
			if (x >= step * 2)
			{
				color = rt_unpack_color(src[off - step * 2]);
				acc.x += color.x; acc.y += color.y; acc.z += color.z;
				count++;
			}
			if (x >= step)
			{
				color = rt_unpack_color(src[off - step]);
				acc.x += color.x; acc.y += color.y; acc.z += color.z;
				count++;
			}
			color = rt_unpack_color(src[off]);
			acc.x += color.x; acc.y += color.y; acc.z += color.z;
			count++;
			if (x + step < width)
			{
				color = rt_unpack_color(src[off + step]);
				acc.x += color.x; acc.y += color.y; acc.z += color.z;
				count++;
			}
			if (x + step * 2 < width)
			{
				color = rt_unpack_color(src[off + step * 2]);
				acc.x += color.x; acc.y += color.y; acc.z += color.z;
				count++;
			}
			acc.x /= (float)count;
			acc.y /= (float)count;
			acc.z /= (float)count;
			dst[off] = rt_pack_color(acc);
			x++;
		}
		y++;
	}
}

static void
blur_vertical(t_gui *gui, size_t step)
{
	t_optimizations	*o;
	uint32_t	*src;
	uint32_t	*dst;
	t_vec3f		acc;
	t_vec3f		color;
	size_t		width;
	size_t		height;
	size_t		x;
	size_t		y;
	size_t		count;
	size_t		off;

	o = &gui->opts;
	src = o->bloom_tmp;
	dst = o->bloom_buf;
	width = gui->win.disp_size.x;
	height = gui->win.disp_size.y;
	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			acc = (t_vec3f){0.0f, 0.0f, 0.0f, 0.0f};
			count = 0;
			off = (y * width + x);
			if (y >= step * 2)
			{
				color = rt_unpack_color(src[off - width * step * 2]);
				acc.x += color.x; acc.y += color.y; acc.z += color.z;
				count++;
			}
			if (y >= step)
			{
				color = rt_unpack_color(src[off - width * step]);
				acc.x += color.x; acc.y += color.y; acc.z += color.z;
				count++;
			}
			color = rt_unpack_color(src[off]);
			acc.x += color.x; acc.y += color.y; acc.z += color.z;
			count++;
			if (y + step < height)
			{
				color = rt_unpack_color(src[off + width * step]);
				acc.x += color.x; acc.y += color.y; acc.z += color.z;
				count++;
			}
			if (y + step * 2 < height)
			{
				color = rt_unpack_color(src[off + width * step * 2]);
				acc.x += color.x; acc.y += color.y; acc.z += color.z;
				count++;
			}
			acc.x /= (float)count;
			acc.y /= (float)count;
			acc.z /= (float)count;
			dst[off] = rt_pack_color(acc);
			x++;
		}
		y++;
	}
}

static void
blend_bloom(t_gui *gui)
{
	t_optimizations	*o;
	uint32_t	*disp;
	t_vec3f		base;
	t_vec3f		glow;
	size_t		width;
	size_t		height;
	size_t		n;
	size_t		i;
	float		intensity;

	o = &gui->opts;
	disp = (uint32_t *)gui->win.addr;
	width = gui->win.disp_size.x;
	height = gui->win.disp_size.y;
	n = width * height;
	intensity = (float)gui->rt_engine.settings.bloom_intensity;
	i = 0;
	while (i < n)
	{
		base = rt_unpack_color(disp[i]);
		glow = rt_unpack_color(o->bloom_buf[i]);
		base.x = fminf(base.x + glow.x * intensity, 255.0f);
		base.y = fminf(base.y + glow.y * intensity, 255.0f);
		base.z = fminf(base.z + glow.z * intensity, 255.0f);
		disp[i] = rt_pack_color(base);
		i++;
	}
}

void
bloom_frame(t_gui *gui)
{
	t_optimizations	*o;
	int				passes;
	size_t			step;
	int				i;
	float			intensity;

	o = &gui->opts;
	if (!o->bloom_buf || !o->bloom_tmp || !gui->win.addr)
		return ;
	intensity = fmaxf((float)gui->rt_engine.settings.bloom_intensity, 0.01f);
	step = (size_t)fmaxf(1.0f, (float)gui->rt_engine.settings.bloom_radius * intensity);
	passes = (int)fmaxf(1.0f, (float)gui->rt_engine.settings.bloom_radius);
	bright_pass(gui);
	i = 0;
	while (i < passes)
	{
		blur_horizontal(gui, step);
		blur_vertical(gui, step);
		i++;
	}
	blend_bloom(gui);
}
