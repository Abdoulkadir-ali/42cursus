/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   worker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/04 12:40:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "optimizations.h"
#include "thread.h"

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

static void	process_worker_tiles(t_render *render)
{
	size_t	id;

	while (1)
	{
		id = __sync_fetch_and_add(&render->next_tile_id, 1);
		if (id >= render->total_tiles)
			break ;
		render_tile(render, id);
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

	sc = render->gui->scene;
	if (!sc || !sc->pool)
		return ;
	task.gui = render->gui;
	task.render = render;
	task.type = TASK_RENDER;
	parallel_run(sc->pool, sc->pool->count, gui_worker, &task);
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
