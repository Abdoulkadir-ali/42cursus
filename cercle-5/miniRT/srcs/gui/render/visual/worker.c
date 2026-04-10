/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   worker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/10 00:56:32 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "optimizations.h"
#include "thread.h"
#include <sys/time.h>

static void	print_tile_done(size_t id, long long d, size_t total)
{
	const char	*tag;

	tag = "";
	if (d > 50)
		tag = " <--- SLOW";
	ft_print_debug("[TILE %zu] Done in %lld ms | Total %zu/%zu (%.1f%%)%s\n",
		id, d, id, total, 100.0 * id / (double)total, tag);
	fflush(stdout);
}

static void	process_worker_tiles(t_render *render)
{
	size_t		id;
	long long	st;
	long long	d;

	while (1)
	{
		id = __sync_fetch_and_add(&render->next_tile_id, 1);
		if (id >= render->total_tiles || render->gui->render.abort_render)
			break ;
		st = now_ms();
		render_tile(render, id);
		d = now_ms() - st;
		if (id == 0 || id % 50 == 0 || d > 10)
			print_tile_done(id, d, render->total_tiles);
	}
}

static void	gui_worker_task(t_gui *gui, t_render_task *task,
	size_t my, size_t n)
{
	size_t	h;

	if (task->type == TASK_SCATTER)
	{
		h = gui->opts.prev_render_size.y;
		scatter_band(gui, (my * h) / n, ((my + 1) * h) / n);
	}
	else if (task->type == TASK_APPLY)
	{
		h = gui->win.disp_size.y;
		apply_reproj_band(gui, (my * h) / n, ((my + 1) * h) / n);
	}
	else if (task->type == TASK_INTERP)
	{
		h = gui->opts.prev_render_size.y;
		interp_band(gui, (my * h) / n, ((my + 1) * h) / n);
	}
	else if (task->type == TASK_TAA)
		taa_band(gui, (my * gui->win.size.y) / n,
			((my + 1) * gui->win.size.y) / n);
	else if (task->type == TASK_BLUR)
		smooth_render_band(gui, (my * gui->win.size.y) / n,
			((my + 1) * gui->win.size.y) / n);
	else
		upscale_band(gui, (my * gui->win.disp_size.y) / n,
			((my + 1) * gui->win.disp_size.y) / n);
}

void	*gui_worker(void *ptr)
{
	t_render_task	*task;
	t_gui			*gui;
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
	gui_worker_task(gui, task, my_idx, count);
	return (NULL);
}
