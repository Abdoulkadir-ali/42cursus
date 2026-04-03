/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 16:26:51 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static void	process_worker_tiles(t_render_pool *pool, size_t idx)
{
	t_render	*render;
	size_t		id;

	render = pool->render[idx];
	while (1)
	{
		id = __sync_fetch_and_add(&render->next_tile_id, 1);
		if (id >= render->total_tiles)
			break ;
		render_tile(render, id);
	}
}

static void	*render_tile_worker(void *ptr)
{
	t_worker		*arg;
	t_render_pool	*pool;
	size_t			idx;

	arg = (t_worker *)ptr;
	pool = arg->pool;
	idx = arg->idx;
	free(arg);
	while (1)
	{
		sem_wait(&pool->start[idx]);
		if (pool->shutdown)
			break ;
		process_worker_tiles(pool, idx);
		sem_post(&pool->done[idx]);
	}
	return (NULL);
}

static void	init_worker(t_render_pool *pool, size_t i)
{
	t_worker	*arg;

	sem_init(&pool->start[i], 0, 0);
	sem_init(&pool->done[i], 0, 0);
	pool->render[i] = NULL;
	arg = malloc(sizeof(t_worker));
	arg->pool = pool;
	arg->idx = i;
	pthread_create(&pool->threads[i], NULL, render_tile_worker, arg);
}

void	init_render_pool(t_render_pool *pool, size_t n)
{
	size_t	i;

	pool->n = n;
	pool->shutdown = false;
	i = 0;
	while (i < n)
		init_worker(pool, i++);
	pool->ready = true;
}

void	render_tiles(t_render *render)
{
	size_t			num_cores;
	size_t			i;
	t_render_pool	*pool;

	num_cores = render->gui->render.num_cores;
	pool = &render->gui->render.pool;
	if (num_cores < 1)
		return ;
	if (!pool->ready)
		init_render_pool(pool, num_cores);
	i = 0;
	while (i < num_cores)
	{
		pool->render[i] = render;
		sem_post(&pool->start[i]);
		i++;
	}
	i = 0;
	while (i < num_cores)
	{
		sem_wait(&pool->done[i]);
		i++;
	}
}
