/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 10:50:12 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/24 20:42:14 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "optimizations.h"

__attribute__((optimize("O3")))
static int	pack_color(t_vec3 color, const t_raytracer_settings *opts,
	t_vec2i pos, size_t frame)
{
	t_vec3f			ch;
	unsigned int	rgb[3];
	float			di;
	uint32_t		h;

	ch = (t_vec3f){(float)color.x, (float)color.y, (float)color.z, 0.0f};
	apply_bcg(&ch, opts);
	h = (uint32_t)pos.x * 374761393U + (uint32_t)pos.y * 668265263U;
	h ^= (uint32_t)frame * 1103515245U;
	h = (h ^ (h >> 13)) * 12741261U;
	di = ((float)(h % 256) / 255.0f - 0.5f) * 1.5f;
	rgb[0] = (unsigned int)(uint8_t)(ch.x + di < 0.0f ? 0.0f : ch.x + di > 255.0f ? 255.0f : ch.x + di) << 16;
	rgb[1] = (unsigned int)(uint8_t)(ch.y + di < 0.0f ? 0.0f : ch.y + di > 255.0f ? 255.0f : ch.y + di) << 8;
	rgb[2] = (unsigned int)(uint8_t)(ch.z + di < 0.0f ? 0.0f : ch.z + di > 255.0f ? 255.0f : ch.z + di);
	return ((rgb[0] | rgb[1] | rgb[2]));
}

static void	apply_dof(t_ray *ray, t_render *render, double x, double y)
{
	const t_raytracer_settings	*s;
	uint64_t					seed;
	t_vec2						ap;
	double						ft;
	t_vec3						fpt;

	s = &render->gui->rt_engine.settings;
	seed = (uint32_t)((int64_t)(x * 73856093) ^ (int64_t)(y * 19349663)
			^ (int64_t)(render->gui->opts.taa_frame * 1664525 + 12345));
	ap.x = 2.0 * PI * rt_rand_d(&seed);
	ap.y = sqrt(rt_rand_d(&seed)) * s->dof_aperture;
	ft = s->dof_focal_dist / fmax(vec3_dot(ray->direction,
				render->transform.forward), 1e-6);
	fpt = vec3_add(ray->origin, vec3_scale(ray->direction, ft));
	ray->origin = vec3_add(ray->origin, vec3_add(
				vec3_scale(render->transform.right, cos(ap.x) * ap.y),
				vec3_scale(render->transform.up, sin(ap.x) * ap.y)));
	ray->direction = vec3_norm(vec3_sub(fpt, ray->origin));
}

__attribute__((optimize("O3")))
static void	make_camera_ray(t_render *render, double x, double y, t_ray *ray)
{
	t_vec2	p;
	t_vec2	j;
	t_vec3	dir;

	j = (t_vec2){0.0, 0.0};
	if (render->gui->opts.taa || render->gui->render.scale > 1)
		taa_get_jitter(render->gui->opts.taa_frame, &j.x, &j.y);
	p.x = (2.0 * (x + 0.5 + j.x) / render->gui->win.size.x - 1.0)
		* render->half_width;
	p.y = (1.0 - 2.0 * (y + 0.5 + j.y) / render->gui->win.size.y)
		* render->half_height;
	dir = vec3_norm(vec3_add(render->transform.forward,
				vec3_add(vec3_scale(render->transform.right, p.x),
					vec3_scale(render->transform.up, p.y))));
	ray_init(ray, render->transform.pos, dir);
	if (render->gui->rt_engine.settings.dof_enabled
		&& render->gui->rt_engine.settings.dof_aperture > 1e-6)
		apply_dof(ray, render, x, y);
	ray->frame_idx = render->gui->opts.taa_frame;
}

__attribute__((optimize("O3")))
void	process_pixel(t_render *render, t_vec2i pos, char *pixel_addr)
{
	t_ray		ray;
	t_vec3		color;
	float		out_t;
	size_t		idx;

	make_camera_ray(render, (double)pos.x, (double)pos.y, &ray);
	out_t = 0.0f;
	color = trace_ray_ex(render->gui->scene->bvh, &ray,
			render->gui->scene, &out_t);
	((uint32_t *)pixel_addr)[0] = (uint32_t)pack_color(color,
			&render->gui->rt_engine.settings, pos, render->gui->opts.taa_frame);
	if (render->gui->opts.depth_buf)
	{
		idx = (size_t)pos.y * (size_t)render->gui->win.size.x + (size_t)pos.x;
		render->gui->opts.depth_buf[idx] = out_t;
	}
}
