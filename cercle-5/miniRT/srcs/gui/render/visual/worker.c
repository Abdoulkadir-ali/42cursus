/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   worker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 00:36:49 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "optimizations.h"
#include "thread.h"
#include <sys/time.h>

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

static void	process_worker_tiles(t_render *render)
{
	size_t		id;
	long long	start;
	long long	duration;

	while (1)
	{
		id = __sync_fetch_and_add(&render->next_tile_id, 1);
		if (id >= render->total_tiles)
			break ;
		if (render->gui->render.abort_render)
			return ;
		start = now_ms();
		render_tile(render, id);
		duration = now_ms() - start;
		if (id == 0 || id % 50 == 0 || duration > 10)
		{
			ft_print_debug("[TILE %zu] Done in %lld ms | Total %zu/%zu (%.1f%%)%s\n",
				id, duration, id, render->total_tiles,
				100.0 * id / (double)render->total_tiles,
				duration > 50 ? " <--- SLOW" : "");
			fflush(stdout);
		}
	}
}

static void	*gui_worker(void *ptr)
{
	t_render_task	*task;
	t_gui			*gui;
	size_t			h;
	size_t			my_idx;
	size_t			count;

	task = (t_render_task *)ptr;
	gui = task->gui;
	if (task->type == TASK_RENDER)
	{
		process_worker_tiles(task->render);
		return (NULL);
	}
	count = gui->scene->pool->count;
	my_idx = atomic_fetch_add(&task->worker_idx, 1) % count;
	if (task->type == TASK_SCATTER)
	{
		h = (size_t)gui->opts.prev_render_size.y;
		scatter_band(gui, (my_idx * h) / count,
			((my_idx + 1) * h) / count);
	}
	else if (task->type == TASK_APPLY)
	{
		h = (size_t)gui->win.disp_size.y;
		apply_reproj_band(gui, (my_idx * h) / count,
			((my_idx + 1) * h) / count);
	}
	else if (task->type == TASK_INTERP)
	{
		h = (size_t)gui->opts.prev_render_size.y;
		interp_band(gui, (my_idx * h) / count,
			((my_idx + 1) * h) / count);
	}
	else if (task->type == TASK_TAA)
	{
		h = (size_t)gui->win.size.y;
		taa_band(gui, (my_idx * h) / count,
			((my_idx + 1) * h) / count);
	}
	else
	{
		h = (size_t)gui->win.disp_size.y;
		upscale_band(gui, (my_idx * h) / count,
			((my_idx + 1) * h) / count);
	}
	return (NULL);
}

void	render_tiles_worker(t_render *render)
{
	t_render_task	task;
	t_scene			*sc;
	long long		start;

	sc = render->gui->scene;
	if (!sc || !sc->pool)
		return ;
	sc->opts = &render->gui->rt_engine.settings;
	task.gui = render->gui;
	task.render = render;
	task.type = TASK_RENDER;
	start = now_ms();
	ft_print_debug("[RENDER] Started tiled rendering...\n");
	parallel_run(sc->pool, sc->pool->count, gui_worker, &task);
	ft_print_debug("[RENDER] Total tiled rendering took %lld ms\n", now_ms() - start);
}

void	gui_parallel_task_worker(t_gui *gui, t_pool_task type)
{
	t_render_task	task;
	t_scene			*sc;

	sc = gui->scene;
	if (!sc || !sc->pool)
		return ;
	task.gui = gui;
	task.render = NULL;
	task.type = type;
	atomic_store(&task.worker_idx, 0);
	parallel_run(sc->pool, sc->pool->count, gui_worker, &task);
}
