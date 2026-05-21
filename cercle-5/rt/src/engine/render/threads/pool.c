/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/08 18:15:34 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "core.h"

static void	tile_task(void *data)
{
	t_tile_job	*job;

	job = (t_tile_job *)data;
	render_tile(job->app, job->tile);
}

int	pool_init(t_thread_pool *p, t_app *app)
{
	int	n;

	memset(p, 0, sizeof(*p));
	p->app = app;
	n = sysconf(_SC_NPROCESSORS_ONLN);
	if (n < 1)
		n = 1;
	if (n > MAX_THREADS)
		n = MAX_THREADS;
	p->n_threads = n;
	pool_rebuild_tiles(p, app->img.w, app->img.h);
	if (!p->tiles || !p->jobs)
		return (-1);
	if (tpool_init(&p->tpool, n) != 0)
		return (-1);
	return (0);
}

void	pool_run(t_thread_pool *p)
{
	int	i;

	if (!p->tiles || !p->jobs || p->n_tiles <= 0)
		return ;
	i = 0;
	while (i < p->n_tiles)
	{
		p->jobs[i].app = p->app;
		p->jobs[i].tile = p->tiles[i];
		tpool_submit(&p->tpool, tile_task, &p->jobs[i++]);
	}
	tpool_wait(&p->tpool);
}

void	pool_destroy(t_thread_pool *p)
{
	tpool_destroy(&p->tpool);
	free(p->tiles);
	free(p->jobs);
	memset(p, 0, sizeof(*p));
}
