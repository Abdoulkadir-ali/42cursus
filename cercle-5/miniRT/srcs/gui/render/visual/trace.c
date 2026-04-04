/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 10:50:12 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/04 08:50:28 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static int	pack_color(t_vec3 color)
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;

	r = ((unsigned int)color.x & 0xFF) << 16;
	g = ((unsigned int)color.y & 0xFF) << 8;
	b = (unsigned int)color.z & 0xFF;
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
	((uint32_t *)pixel_addr)[0] = (uint32_t)pack_color(color);
}
