/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parallel.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 11:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/09 03:20:39 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thread.h"
#include "debug.h"

static void	exec_worker(t_thread_pool *pool, size_t *my_gen)
{
	t_worker_func	f;
	void			*data;

	*my_gen = pool->generation;
	f = pool->worker;
	data = pool->data;
	pthread_mutex_unlock(&pool->lock);
	f(data);
	if (atomic_fetch_sub(&pool->running, 1) == 1)
	{
		pthread_mutex_lock(&pool->lock);
		pthread_cond_signal(&pool->cond_done);
		pthread_mutex_unlock(&pool->lock);
	}
}

static void	*pool_worker(void *arg)
{
	t_thread_pool	*pool;
	size_t			my_gen;

	pool = (t_thread_pool *)arg;
	my_gen = 0;
	while (1)
	{
		pthread_mutex_lock(&pool->lock);
		while (!pool->stop && pool->generation == my_gen)
			pthread_cond_wait(&pool->cond_work, &pool->lock);
		if (pool->stop)
		{
			pthread_mutex_unlock(&pool->lock);
			break ;
		}
		exec_worker(pool, &my_gen);
	}
	return (NULL);
}

void	threads_init(t_thread_pool *pool)
{
	size_t	i;

	if (!pool || pool->initialized)
		return ;
	pool->count = sysconf(_SC_NPROCESSORS_ONLN);
	if (pool->count < 1)
		pool->count = 1;
	pool->threads = malloc(sizeof(pthread_t) * pool->count);
	if (!pool->threads)
		return ;
	pthread_mutex_init(&pool->lock, NULL);
	pthread_cond_init(&pool->cond_work, NULL);
	pthread_cond_init(&pool->cond_done, NULL);
	pool->worker = NULL;
	pool->generation = 0;
	pool->stop = false;
	pool->initialized = true;
	i = 0;
	while (i < pool->count)
		pthread_create(&pool->threads[i++], NULL, pool_worker, pool);
}

void	threads_destroy(t_thread_pool *pool)
{
	size_t	i;

	if (!pool || !pool->initialized)
		return ;
	pthread_mutex_lock(&pool->lock);
	pool->stop = true;
	pthread_cond_broadcast(&pool->cond_work);
	pthread_mutex_unlock(&pool->lock);
	i = 0;
	while (i < pool->count)
		pthread_join(pool->threads[i++], NULL);
	free(pool->threads);
	pthread_mutex_destroy(&pool->lock);
	pthread_cond_destroy(&pool->cond_work);
	pthread_cond_destroy(&pool->cond_done);
	pool->initialized = false;
}

void	parallel_run(t_thread_pool *pool, size_t count,
		t_worker_func worker, void *data)
{
	if (count == 0)
		return ;
	if (!pool)
	{
		worker(data);
		return ;
	}
	if (!pool->initialized)
		threads_init(pool);
	pthread_mutex_lock(&pool->lock);
	pool->worker = worker;
	pool->data = data;
	atomic_store(&pool->running, pool->count);
	pool->generation++;
	pthread_cond_broadcast(&pool->cond_work);
	while (atomic_load(&pool->running) > 0)
		pthread_cond_wait(&pool->cond_done, &pool->lock);
	pool->worker = NULL;
	pthread_mutex_unlock(&pool->lock);
}
