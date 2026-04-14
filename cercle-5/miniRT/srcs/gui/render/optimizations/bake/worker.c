/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bake_worker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/12 01:20:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "optimizations.h"
#include <math.h>

static void	bake_render_frame(t_bake_job *job, t_gui *fake)
{
	t_render	r;
	double		hh;
	size_t		id;

	r.gui = fake;
	r.next_tile_id = 0;
	r.step = 1;
	r.transform = job->camera;
	r.aspect_ratio = (double)job->width / (double)job->height;
	hh = tan(job->fov * 0.5 * PI / 180.0);
	r.half_height = hh;
	r.half_width = hh * r.aspect_ratio;
	r.tiles_count.x = (job->width + TILE_SIZE - 1) / TILE_SIZE;
	r.tiles_count.y = (job->height + TILE_SIZE - 1) / TILE_SIZE;
	r.total_tiles = ((r.tiles_count.x + 3) / 4)
		* ((r.tiles_count.y + 3) / 4) * 16;
	id = 0;
	while (id < r.total_tiles && !job->cancel)
		render_tile(&r, id++);
}

static void	bake_accum(t_bake_job *job)
{
	uint32_t	*px;
	size_t		i;
	t_vec3i		c;

	px = job->pixel_scratch;
	i = 0;
	while (i < (size_t)job->width * (size_t)job->height)
	{
		c = rt_unpack_color_v(px[i]);
		job->accum_r[i] += (uint32_t)c.x;
		job->accum_g[i] += (uint32_t)c.y;
		job->accum_b[i] += (uint32_t)c.z;
		i++;
	}
	job->frame++;
}

static void	bake_loop(t_bake_job *job, t_gui *fake)
{
	while (job->frame < job->target && !job->cancel)
	{
		fake->opts.taa_frame = job->frame;
		bake_render_frame(job, fake);
		bake_accum(job);
	}
}

static void	init_bake_gui(t_gui *f, t_bake_job *j)
{
	ft_memcpy(f, j->gui, sizeof(t_gui));
	f->win.addr = (char *)j->pixel_scratch;
	f->win.size.x = (size_t)j->width;
	f->win.size.y = (size_t)j->height;
	f->win.line_len = j->width * 4;
	f->win.bpp = BAKE_BPP;
	f->rt_engine.settings = j->settings;
	f->render.scale = 1;
	f->opts.taa = true;
	f->scene = j->scene_snap;
	f->scene->opts = &f->rt_engine.settings;
}

void	*bake_thread(void *arg)
{
	t_bake_job	*j;
	t_gui		*f;

	j = (t_bake_job *)arg;
	f = malloc(sizeof(t_gui));
	if (!f)
	{
		j->running = false;
		j->done = true;
		return (NULL);
	}
	init_bake_gui(f, j);
	bake_loop(j, f);
	if (!j->cancel)
		bake_save(j);
	j->done_ts = now_ms();
	free(f);
	j->running = false;
	j->done = true;
	return (NULL);
}
