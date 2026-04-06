/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 10:50:12 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 12:19:12 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "optimizations.h"

/*
** apply_brightness: bias by (brightness-50)/50 * 255 additive.
** apply_contrast:   S-curve around midpoint 0.5; factor = contrast/50.
** apply_saturation: lerp each channel toward luminance; factor = sat/50.
** apply_gamma:      gamma = 50/gamma_val (neutral=50 → exponent 1.0).
**                   Uses fast sqrt chains to avoid powf when possible.
*/
static int	pack_color(t_vec3 color, const t_raytracer_settings *opts)
{
	t_vec3f			ch;
	unsigned int	rgb[3];

	ch.x = (float)color.x;
	ch.y = (float)color.y;
	ch.z = (float)color.z;
	apply_bcg(&ch, opts);
	rgb[0] = ((unsigned int)(uint8_t)ch.x) << 16;
	rgb[1] = ((unsigned int)(uint8_t)ch.y) << 8;
	rgb[2] = (unsigned int)(uint8_t)ch.z;
	return ((rgb[0] | rgb[1] | rgb[2]));
}

static void	make_camera_ray(t_render *render, double x, double y, t_ray *ray)
{
	double	px;
	double	py;
	t_vec3	dir;
	double	jx;
	double	jy;

	jx = 0.0;
	jy = 0.0;
	if (render->gui->opts.taa)
		taa_get_jitter(render->gui->opts.taa_frame, &jx, &jy);
	px = (2.0 * (x + 0.5 + jx) / render->gui->win.size.x - 1.0)
		* render->half_width;
	py = (1.0 - 2.0 * (y + 0.5 + jy) / render->gui->win.size.y)
		* render->half_height;
	dir = vec3_norm(vec3_add(render->transform.forward,
				vec3_add(vec3_scale(render->transform.right, px),
					vec3_scale(render->transform.up, py))));
	ray_init(ray, render->transform.pos, dir);
}

void	process_pixel(t_render *render, t_vec2i pos, char *pixel_addr)
{
	t_ray		ray;
	t_vec3		color;
	int			color_packed;
	float		out_t;
	size_t		idx;

	make_camera_ray(render, (double)pos.x, (double)pos.y, &ray);
	out_t = 0.0f;
	color = trace_ray_ex(render->gui->scene->bvh, &ray,
			render->gui->scene, &out_t);
	color_packed = pack_color(color, &render->gui->rt_engine.settings);
	((uint32_t *)pixel_addr)[0] = (uint32_t)color_packed;
	if (render->gui->opts.depth_buf)
	{
		idx = pos.y * render->gui->win.size.x + pos.x;
		render->gui->opts.depth_buf[idx] = out_t;
	}
}
