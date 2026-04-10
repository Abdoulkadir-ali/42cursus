/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 10:50:12 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/10 00:17:56 by abdoali          ###   ########.fr       */
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
static int	pack_color(t_vec3 color, const t_raytracer_settings *opts,
	t_vec2i pos, size_t frame)
{
	t_vec3f			ch;
	unsigned int	rgb[3];
	float			dither;
	uint32_t		h;

	ch.x = (float)color.x;
	ch.y = (float)color.y;
	ch.z = (float)color.z;
	apply_bcg(&ch, opts);
	/* Spatial Dithering: break banding into temporal noise */
	h = (uint32_t)pos.x * 374761393U + (uint32_t)pos.y * 668265263U;
	h ^= (uint32_t)frame * 1103515245U;
	h = (h ^ (h >> 13)) * 12741261U;
	dither = ((float)(h % 256) / 255.0f - 0.5f) * 1.5f;
	rgb[0] = (unsigned int)(uint8_t)clamp_d(ch.x + dither, 0, 255) << 16;
	rgb[1] = (unsigned int)(uint8_t)clamp_d(ch.y + dither, 0, 255) << 8;
	rgb[2] = (unsigned int)(uint8_t)clamp_d(ch.z + dither, 0, 255);
	return ((rgb[0] | rgb[1] | rgb[2]));
}

static void	make_camera_ray(t_render *render, double x, double y, t_ray *ray)
{
	double				px;
	double				py;
	t_vec3				dir;
	double				jx;
	double				jy;
	t_vec3				origin;
	const t_raytracer_settings	*s;

	s = &render->gui->rt_engine.settings;
	jx = 0.0;
	jy = 0.0;
	/* Always jitter if TAA or any Rescaling is active */
	if (render->gui->opts.taa || render->gui->render.scale > 1)
		taa_get_jitter(render->gui->opts.taa_frame, &jx, &jy);
	px = (2.0 * (x + 0.5 + jx) / render->gui->win.size.x - 1.0)
		* render->half_width;
	py = (1.0 - 2.0 * (y + 0.5 + jy) / render->gui->win.size.y)
		* render->half_height;
	dir = vec3_norm(vec3_add(render->transform.forward,
				vec3_add(vec3_scale(render->transform.right, px),
					vec3_scale(render->transform.up, py))));
	origin = render->transform.pos;
	if (s->dof_enabled && s->dof_aperture > 1e-6)
	{
		uint32_t	seed;
		double		angle;
		double		radius;
		double		focal_t;
		t_vec3		focus_pt;
		seed = (uint32_t)((int64_t)(x * 73856093)
			^ (int64_t)(y * 19349663)
			^ (int64_t)(render->gui->opts.taa_frame * 1664525 + 12345));
		angle = 2.0 * PI * rt_rand_d(&seed);
		radius = sqrt(rt_rand_d(&seed)) * s->dof_aperture;
		focal_t = s->dof_focal_dist
			/ fmax(vec3_dot(dir, render->transform.forward), 1e-6);
		focus_pt = vec3_add(origin, vec3_scale(dir, focal_t));
		origin = vec3_add(origin,
				vec3_add(
					vec3_scale(render->transform.right, cos(angle) * radius),
					vec3_scale(render->transform.up, sin(angle) * radius)));
		dir = vec3_norm(vec3_sub(focus_pt, origin));
	}
	ray_init(ray, origin, dir);
	ray->frame_idx = render->gui->opts.taa_frame;
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
	color_packed = pack_color(color, &render->gui->rt_engine.settings,
			pos, render->gui->opts.taa_frame);
	((uint32_t *)pixel_addr)[0] = (uint32_t)color_packed;
	if (render->gui->opts.depth_buf)
	{
		idx = pos.y * render->gui->win.size.x + pos.x;
		render->gui->opts.depth_buf[idx] = out_t;
	}
}
