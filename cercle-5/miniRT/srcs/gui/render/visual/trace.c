/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 10:50:12 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/05 21:30:25 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

/*
** apply_brightness: bias by (brightness-50)/50 * 255 additive.
** apply_contrast:   S-curve around midpoint 0.5; factor = contrast/50.
** apply_saturation: lerp each channel toward luminance; factor = sat/50.
** apply_gamma:      gamma = 50/gamma_val (neutral=50 → exponent 1.0).
**                   Uses fast sqrt chains to avoid powf when possible.
*/
static void	apply_saturation(float ch[3], double sat)
{
	float	luma;
	float	f;

	f = (float)(sat / 50.0);
	luma = 0.299f * ch[0] + 0.587f * ch[1] + 0.114f * ch[2];
	ch[0] = luma + f * (ch[0] - luma);
	ch[1] = luma + f * (ch[1] - luma);
	ch[2] = luma + f * (ch[2] - luma);
}

static float	apply_gamma_ch(float c, double gamma_val)
{
	float	x;
	float	exp;

	if (c <= 0.0f)
		return (0.0f);
	x = c / 255.0f;
	exp = (float)(50.0 / gamma_val);
	/* fast path for common exponents */
	if (exp >= 0.49f && exp <= 0.51f)
		x = sqrtf(x);
	else if (exp >= 0.44f && exp <= 0.46f)
		x = sqrtf(sqrtf(x)) * sqrtf(sqrtf(sqrtf(x)));
	else
		x = powf(x, exp);
	return (x * 255.0f);
}

static int	pack_color(t_vec3 color, const t_raytracer_settings *opts)
{
	float			ch[3];
	float			bfac;
	float			cfac;
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
	int				i;

	ch[0] = (float)color.x;
	ch[1] = (float)color.y;
	ch[2] = (float)color.z;
	bfac = (float)((opts->brightness - 50.0) / 50.0) * 255.0f;
	cfac = (float)(opts->contrast / 50.0);
	i = 0;
	while (i < 3)
	{
		ch[i] += bfac;
		ch[i] = (ch[i] / 255.0f - 0.5f) * cfac * 255.0f + 127.5f;
		i++;
	}
	apply_saturation(ch, opts->saturation);
	i = 0;
	while (i < 3)
	{
		if (opts->gamma > 0.5)
			ch[i] = apply_gamma_ch(ch[i], opts->gamma);
		ch[i] = fminf(fmaxf(ch[i], 0.0f), 255.0f);
		i++;
	}
	r = ((unsigned int)(uint8_t)ch[0]) << 16;
	g = ((unsigned int)(uint8_t)ch[1]) << 8;
	b = (unsigned int)(uint8_t)ch[2];
	return ((int)(r | g | b));
}


static void	make_camera_ray(t_render *render, double x, double y, t_ray *ray)
{
	double	px;
	double	py;
	t_vec3	dir;

	px = (2.0 * (x + 0.5) / render->gui->win.size.x - 1.0) * render->half_width;
	py = (1.0 - 2.0 * (y + 0.5) / render->gui->win.size.y) * render->half_height;
	dir = vec3_norm(vec3_add(render->transform.forward,
				vec3_add(vec3_scale(render->transform.right, px),
					vec3_scale(render->transform.up, py))));
	ray_init(ray, render->transform.pos, dir);
}

void	process_pixel(t_render *render, t_vec2i pos, char *pixel_addr)
{
	t_ray	ray;
	t_vec3	color;
	float	out_t;
	int		idx;

	make_camera_ray(render, (double)pos.x, (double)pos.y, &ray);
	color = trace_ray_ex(render->gui->scene->bvh, &ray,
			render->gui->scene, &out_t);
	idx = pos.y * render->gui->win.size.x + pos.x;
	if (render->gui->render.depth_buf)
		render->gui->render.depth_buf[idx] = out_t;
	((uint32_t *)pixel_addr)[0] = (uint32_t)pack_color(color,
			&render->gui->rt_engine.settings);
}
