/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 02:45:58 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "thread.h"

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
	ft_print_debug("[RENDER] Start tiling...\n");
	parallel_run(sc->pool, sc->pool->count, gui_worker, &task);
	ft_print_debug("[RENDER] Tiles done in %lld ms\n", now_ms() - start);
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
