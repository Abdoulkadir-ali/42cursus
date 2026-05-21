/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   taa.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 18:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 17:28:51 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "core.h"
#include <string.h>

void	taa_reproject(t_app *app)
{
	int		x;
	int		y;
	int		px;
	int		py;
	float	sx;
	float	sy;
	float	d;
	t_vec3	p;
	float	*src;
	float	*dst;

	if (!app->accum || !app->taa_scratch || !app->depth_buffer)
		return ;
	memcpy(app->taa_scratch, app->accum,
		sizeof(float) * app->accum_w * app->accum_h * 3);
	memset(app->accum, 0, sizeof(float) * app->accum_w * app->accum_h * 3);
	for (y = 0; y < app->accum_h; y++)
	{
		for (x = 0; x < app->accum_w; x++)
		{
			d = app->depth_buffer[y * app->accum_w + x];
			if (d >= T_MAX * 0.9f)
				continue ;
			/* Reconstruct 3D point from previous camera and depth */
			t_vec3 dir = primary_ray(&app->scene.cam_prev,
				(float)x + 0.5f, (float)y + 0.5f,
				app->img.w, app->img.h, 0, 0).d;
			p = v3_add(app->scene.cam_prev.pos, v3_mul(dir, d));
			/* Project into previous camera */
			if (project_to_camera(&app->scene.cam_prev, p,
				app->img.w, app->img.h, &sx, &sy))
			{
				px = (int)sx;
				py = (int)sy;
				src = &app->taa_scratch[(py * app->accum_w + px) * 3];
				dst = &app->accum[(y * app->accum_w + x) * 3];
				dst[0] = src[0];
				dst[1] = src[1];
				dst[2] = src[2];
			}
		}
	}
}
