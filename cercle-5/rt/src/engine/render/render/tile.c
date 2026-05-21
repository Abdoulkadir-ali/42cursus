/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tile.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 18:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/02 17:30:30 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "core.h"
#include <math.h>
#include <stdatomic.h>

static void	put_block(t_image *img, int x, int y, int bs, unsigned int color)
{
	int	iy;
	int	ix;
	char	*row;

	iy = 0;
	while (iy < bs && y + iy < img->h)
	{
		row = img->addr + (y + iy) * img->line_len;
		ix = 0;
		while (ix < bs && x + ix < img->w)
		{
			*(unsigned int *)(row + (x + ix) * 4) = color;
			ix++;
		}
		iy++;
	}
}

static inline float	tonemap_pixel(float linear, float exposure)
{
	float	c;

	c = fmaxf(0.0f, linear * exposure);
	c = c / (1.0f + c);
	return (sqrtf(c));
}

static inline t_vec3	apply_visual(t_vec3 c, const t_render_settings *s,
								float nx, float ny)
{
	float	lum;
	float	vig;
	float	dx;
	float	dy;

	c.x = fmaxf(0.0f, c.x * s->exposure);
	c.y = fmaxf(0.0f, c.y * s->exposure);
	c.z = fmaxf(0.0f, c.z * s->exposure);
	lum = c.x * 0.2126f + c.y * 0.7152f + c.z * 0.0722f;
	c.x = lum + s->saturation * (c.x - lum);
	c.y = lum + s->saturation * (c.y - lum);
	c.z = lum + s->saturation * (c.z - lum);
	c.x = (c.x - 0.5f) * s->contrast + 0.5f + s->brightness;
	c.y = (c.y - 0.5f) * s->contrast + 0.5f + s->brightness;
	c.z = (c.z - 0.5f) * s->contrast + 0.5f + s->brightness;
	c.x = fmaxf(0.0f, c.x);
	c.y = fmaxf(0.0f, c.y);
	c.z = fmaxf(0.0f, c.z);
	if (s->vignette > 0.0f)
	{
		dx = nx * 2.0f - 1.0f;
		dy = ny * 2.0f - 1.0f;
		vig = 1.0f - s->vignette * (dx * dx + dy * dy);
		if (vig < 0.0f)
			vig = 0.0f;
		c.x *= vig;
		c.y *= vig;
		c.z *= vig;
	}
	c.x = c.x / (1.0f + lum);
	c.y = c.y / (1.0f + lum);
	c.z = c.z / (1.0f + lum);
	c.x = powf(fmaxf(0.0f, c.x), 1.0f / s->gamma);
	c.y = powf(fmaxf(0.0f, c.y), 1.0f / s->gamma);
	c.z = powf(fmaxf(0.0f, c.z), 1.0f / s->gamma);
	return (c);
}

void	render_tile(t_app *app, t_tile t)
{
	int		x;
	int		y;
	t_ray	r;
	t_hit	h;
	t_vec3	col;
	int		hit;
	int		bs;
	int		absorbed;
	int		use_acc;
	int		sample;
	float	jx;
	float	jy;
	float	*acc;
	float	inv;
	t_vec3	disp;

	bs = app->set.render.downscale;
	if (bs < 1)
		bs = 1;
	use_acc = (app->set.render.progressive && bs == 1 && app->accum
		&& app->accum_w == app->img.w && app->accum_h == app->img.h);
	sample = app->accum_samples;
	jx = 0.5f;
	jy = 0.5f;
	if (use_acc && sample > 0)
	{
		jx = halton(sample + 1, 2);
		jy = halton(sample + 1, 3);
	}
	y = t.y0;
	while (y < t.y1)
	{
		x = t.x0;
		while (x < t.x1)
		{
			r = primary_ray(&app->scene.cam,
					(float)x + jx * (float)bs,
					(float)y + jy * (float)bs,
					app->img.w, app->img.h,
					halton(sample + 1, 5) * 2.0f - 1.0f,
					halton(sample + 1, 7) * 2.0f - 1.0f);
			absorbed = 0;
			if (app->set.rt.lensing_on && app->scene.n_bhs > 0)
				absorbed = ray_bend_blackholes(&app->scene, &r);
			h.t = T_MAX;
			if (absorbed)
			{
				col = v3(0, 0, 0);
				hit = 0;
			}
			else
			{
				hit = bvh_traverse(&app->bvh, &r, &h, app->scene.bvh_objs);
				hit |= hit_planes(app->scene.planes, app->scene.n_planes,
						&r, &h);
				if (hit)
					col = shade(app, &r, &h, 0);
				else
					col = sky_color(r.d);
			}
			if (use_acc)
			{
				acc = &app->accum[(y * app->accum_w + x) * 3];
				if (sample == 0)
				{
					acc[0] = col.x;
					acc[1] = col.y;
					acc[2] = col.z;
				}
				else
				{
					acc[0] += col.x;
					acc[1] += col.y;
					acc[2] += col.z;
				}
				inv = 1.0f / (float)(sample + 1);
				disp = v3(acc[0] * inv, acc[1] * inv, acc[2] * inv);
				if (app->depth_buffer)
					app->depth_buffer[y * app->accum_w + x] = hit ? h.t : 1e30f;
			}
			else
				disp = col;
			{
				t_vec3	out;
				float	nx;
				float	ny;

				nx = (float)x / (float)app->img.w;
				ny = (float)y / (float)app->img.h;
				out = apply_visual(disp, &app->set.render, nx, ny);
				put_block(&app->img, x, y, bs, (unsigned int)
					ft_argb(out.x, out.y, out.z));
			}
			if (app->set.render.pick_buffer && app->pick.ids && y < app->pick.h && x < app->pick.w)
				app->pick.ids[y * app->pick.w + x] = hit ? h.obj_index
					: 0x7fffffff;
			x += bs;
		}
		atomic_thread_fence(memory_order_release);
		y += bs;
	}
}
