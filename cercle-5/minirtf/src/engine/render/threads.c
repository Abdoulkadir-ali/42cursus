/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 18:47:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/25 03:26:56 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "core.h"
#include <stdatomic.h>
#include <unistd.h>

void	render_tile(t_app *app, t_tile t);

void	pool_rebuild_tiles(t_thread_pool *p, int w, int h)
{
	int	tx;
	int	ty;
	int	nx;
	int	ny;
	int	i;

	nx = (w + TILE_SIZE - 1) / TILE_SIZE;
	ny = (h + TILE_SIZE - 1) / TILE_SIZE;
	p->n_tiles = nx * ny;
	if (p->n_tiles > p->cap_tiles)
	{
		free(p->tiles);
		p->tiles = (t_tile *)malloc(sizeof(t_tile) * p->n_tiles);
		p->cap_tiles = p->n_tiles;
	}
	if (!p->tiles)
		return ;
	i = 0;
	ty = 0;
	while (ty < ny)
	{
		tx = 0;
		while (tx < nx)
		{
			p->tiles[i].x0 = tx * TILE_SIZE;
			p->tiles[i].y0 = ty * TILE_SIZE;
			p->tiles[i].x1 = (p->tiles[i].x0 + TILE_SIZE > w)
				? w : p->tiles[i].x0 + TILE_SIZE;
			p->tiles[i].y1 = (p->tiles[i].y0 + TILE_SIZE > h)
				? h : p->tiles[i].y0 + TILE_SIZE;
			i++;
			tx++;
		}
		ty++;
	}
}

static void	*worker(void *arg)
{
	t_thread_pool	*p;
	int				idx;

	p = (t_thread_pool *)arg;
	while (1)
	{
		pthread_mutex_lock(&p->mtx);
		idx = p->next_tile;
		if (idx < p->n_tiles)
			p->next_tile = idx + 1;
		pthread_mutex_unlock(&p->mtx);
		if (idx >= p->n_tiles || !p->tiles)
			break ;
		render_tile(p->app, p->tiles[idx]);
	}
	return (NULL);
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
	if (pthread_mutex_init(&p->mtx, NULL) != 0)
		return (-1);
	pool_rebuild_tiles(p, app->img.w, app->img.h);
	if (!p->tiles)
		return (-1);
	return (0);
}

void	pool_run(t_thread_pool *p)
{
	int	i;

	if (!p->tiles || p->n_tiles <= 0)
		return ;
	pthread_mutex_lock(&p->mtx);
	p->next_tile = 0;
	pthread_mutex_unlock(&p->mtx);
	i = 0;
	while (i < p->n_threads)
	{
		if (pthread_create(&p->tids[i], NULL, worker, p) != 0)
			break ;
		i++;
	}
	while (--i >= 0)
		pthread_join(p->tids[i], NULL);
}

void	pool_destroy(t_thread_pool *p)
{
	free(p->tiles);
	pthread_mutex_destroy(&p->mtx);
	memset(p, 0, sizeof(*p));
}