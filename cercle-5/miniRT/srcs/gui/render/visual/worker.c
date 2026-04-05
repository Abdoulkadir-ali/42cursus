/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   worker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/05 18:02:21 by abdoali          ###   ########.fr       */
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
		if (__sync_fetch_and_add(&render->gui->render.abort_render, 0))
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
	size_t			band;
	static size_t	idx = 0;
	size_t			my_idx;

	task = (t_render_task *)ptr;
	gui = task->gui;
	if (task->type == TASK_RENDER)
		process_worker_tiles(task->render);
	else
	{
		my_idx = __sync_fetch_and_add(&idx, 1) % gui->scene->pool->count;
		if (task->type == TASK_SCATTER)
			h = (size_t)gui->render.prev_render_size.y;
		else
			h = (size_t)gui->win.disp_size.y;
		band = (h + gui->scene->pool->count - 1) / gui->scene->pool->count;
		if (task->type == TASK_SCATTER)
			scatter_band(gui, my_idx * band, MIN((my_idx + 1) * band, h));
		else if (task->type == TASK_APPLY)
			apply_reproj_band(gui, my_idx * band, MIN((my_idx + 1) * band, h));
		else if (task->type == TASK_UPSCALE)
			upscale_band(gui, (my_idx * gui->win.disp_size.y) / gui->scene->pool->count,
				((my_idx + 1) * gui->win.disp_size.y) / gui->scene->pool->count);
		if (my_idx == gui->scene->pool->count - 1)
			idx = 0;
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
	parallel_run(sc->pool, sc->pool->count, gui_worker, &task);
}
