/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bake_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/12 02:50:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "optimizations.h"
#include <stdio.h>

static size_t	g_bake_num = 0;

static t_bake_job	*bake_job_alloc(t_gui *gui)
{
	t_bake_job	*job;
	size_t		n;

	job = ft_calloc(1, sizeof(t_bake_job));
	if (!job)
		return (NULL);
	n = (size_t)gui->win.disp_size.x * (size_t)gui->win.disp_size.y;
	job->accum_r = ft_calloc(n, sizeof(uint32_t));
	job->accum_g = ft_calloc(n, sizeof(uint32_t));
	job->accum_b = ft_calloc(n, sizeof(uint32_t));
	job->pixel_scratch = ft_calloc(n, sizeof(uint32_t));
	if (!job->accum_r || !job->accum_g || !job->accum_b || !job->pixel_scratch)
	{
		free(job->accum_r);
		free(job->accum_g);
		free(job->accum_b);
		free(job->pixel_scratch);
		free(job);
		return (NULL);
	}
	return (job);
}

static bool	bake_scene_snap(t_gui *gui, t_bake_job *job)
{
	t_scene	*snap;

	snap = malloc(sizeof(t_scene));
	if (!snap)
		return (false);
	ft_memcpy(snap, gui->scene, sizeof(t_scene));
	snap->bvh = bvh_create(gui->scene);
	pthread_rwlock_init(&snap->bvh_lock, NULL);
	job->scene_snap = snap;
	return (true);
}

static void	init_job_data(t_gui *gui, t_bake_job *job)
{
	job->width = (int)gui->win.disp_size.x;
	job->height = (int)gui->win.disp_size.y;
	job->fov = gui->scene->camera.fov;
	job->target = BAKE_FRAMES;
	job->gui = gui;
	job->camera = gui->scene->camera.transform;
	job->settings = gui->rt_engine.settings;
	job->settings.draft_mode = false;
}

void	bake_job_start(t_gui *gui)
{
	t_bake_job	*job;

	if (gui->render.bake_job && gui->render.bake_job->running)
		return ;
	if (gui->render.bake_job)
		bake_job_cancel(gui);
	job = bake_job_alloc(gui);
	if (!job)
		return ;
	init_job_data(gui, job);
	if (!bake_scene_snap(gui, job))
	{
		free(job->accum_r);
		free(job->accum_g);
		free(job->accum_b);
		free(job->pixel_scratch);
		return (free(job));
	}
	snprintf(job->out_path, BAKE_NAME_LEN, "bake_%04zu.bmp", ++g_bake_num);
	job->running = true;
	gui->render.bake_job = job;
	pthread_create(&job->thread, NULL, bake_thread, job);
}
