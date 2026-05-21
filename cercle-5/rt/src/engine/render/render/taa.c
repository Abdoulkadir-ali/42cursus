/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   taa.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 18:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/08 18:49:54 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "core.h"
#include <string.h>

static void	taa_rows(const t_app *app, int y0, int y1)
{
	int		x;
	int		y;
	int		px;
	int		py;
	float	sx;
	float	sy;
	float	d;
	t_vec3	p;
	t_vec3	dir;
	float	*src;
	float	*dst;

	y = y0;
	while (y < y1)
	{
		x = 0;
		while (x < app->accum_w)
		{
			d = app->depth_buffer[y * app->accum_w + x];
			if (d < T_MAX * 0.9f)
			{
				dir = primary_ray(&app->scene.cam_prev,
					(float)x + 0.5f, (float)y + 0.5f,
					app->img.w, app->img.h, 0, 0).d;
				p = v3_add(app->scene.cam_prev.pos, v3_mul(dir, d));
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
			x++;
		}
		y++;
	}
}

static void	taa_chunk(void *data)
{
	t_taa_job	*j;

	j = (t_taa_job *)data;
	taa_rows(j->app, j->y0, j->y1);
}

void	taa_reproject(t_app *app)
{
	t_tpool	*tp;
	int		w;
	int		chunk;
	int		i;

	if (!app->accum || !app->taa_scratch || !app->depth_buffer)
		return ;
	memcpy(app->taa_scratch, app->accum,
		sizeof(float) * app->accum_w * app->accum_h * 3);
	memset(app->accum, 0, sizeof(float) * app->accum_w * app->accum_h * 3);
	tp = &app->pool.tpool;
	w = tp->n_workers;
	if (w <= 1 || app->accum_h < 32)
	{
		taa_rows(app, 0, app->accum_h);
		return ;
	}
	chunk = (app->accum_h + w - 1) / w;
	i = 0;
	while (i < w)
	{
		app->pool.taa_jobs[i].app = app;
		app->pool.taa_jobs[i].y0 = i * chunk;
		app->pool.taa_jobs[i].y1 = i * chunk + chunk;
		if (app->pool.taa_jobs[i].y1 > app->accum_h)
			app->pool.taa_jobs[i].y1 = app->accum_h;
		if (app->pool.taa_jobs[i].y0 < app->accum_h)
			tpool_submit(tp, taa_chunk, &app->pool.taa_jobs[i]);
		i++;
	}
	tpool_wait(tp);
}

