/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 10:50:12 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 13:46:37 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static int	pack_color(t_vec3 color)
{
	int	r;
	int	g;
	int	b;

	r = ((int)color.x & 0xFF) << 16;
	g = ((int)color.y & 0xFF) << 8;
	b = (int)color.z & 0xFF;
	return (r | g | b);
}

static void	fill_block(t_render *render)
{
	t_vec2i		d;
	t_vec2i		lim;
	uint32_t	*dst;

	lim = render->gui->win.size;
	d.y = 0;
	while (d.y < render->step && render->pos.y + d.y < lim.y)
	{
		dst = (uint32_t *)(render->pixel_addr + (d.y
					* render->gui->win.line_len));
		d.x = 0;
		while (d.x < render->step && render->pos.x + d.x < lim.x)
		{
			dst[d.x] = render->color;
			d.x++;
		}
		d.y++;
	}
}

static void	make_camera_ray(t_render *render, double x, double y, t_ray *ray)
{
	double	px;
	double	py;
	t_vec3	dir;

	px = (2.0 * (x + 0.5) / render->gui->win.size.x - 1.0) * render->half_width
		* render->aspect_ratio;
	py = (1.0 - 2.0 * (y + 0.5) / render->gui->win.size.y) * render->half_height
		* render->aspect_ratio;
	dir = vec3_norm(vec3_add(render->transform.forward,
				vec3_add(vec3_scale(render->transform.right, px),
					vec3_scale(render->transform.up, py))));
	ray_init(ray, render->transform.pos, dir);
}

void	process_pixel(t_render *render, t_vec2i pos, char *pixel_addr)
{
	t_ray		ray;
	t_vec3		color;
	uint32_t	*dst;

	make_camera_ray(render, (double)pos.x, (double)pos.y, &ray);
	color = trace_ray(render->gui->scene->bvh, &ray, render->gui->scene);
	render->pos = pos;
	render->color = pack_color(color);
	render->pixel_addr = pixel_addr;
	if (render->step > 1)
		fill_block(render);
	else
	{
		dst = (uint32_t *)render->pixel_addr;
		*dst = render->color;
	}
}
