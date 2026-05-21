/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_pool.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/08 19:38:05 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "threads.h"

/*
** Each worker blocks on work_cond when the queue is empty.
** After executing a task it decrements active; when active reaches 0 and
** the queue is also empty it broadcasts on done_cond so tpool_wait() returns.
*/
static void	*tpool_worker(void *arg)
{
	t_tpool			*tp;
	t_tpool_task	task;

	tp = (t_tpool *)arg;
	while (1)
	{
		pthread_mutex_lock(&tp->mtx);
		while (tp->q_size == 0 && !tp->shutdown)
			pthread_cond_wait(&tp->work_cond, &tp->mtx);
		if (tp->shutdown && tp->q_size == 0)
		{
			pthread_mutex_unlock(&tp->mtx);
			return (NULL);
		}
		task = tp->queue[tp->q_head];
		tp->q_head = (tp->q_head + 1) % tp->q_cap;
		tp->q_size--;
		tp->active++;
		pthread_mutex_unlock(&tp->mtx);
		task.fn(task.data);
		pthread_mutex_lock(&tp->mtx);
		tp->active--;
		if (tp->active == 0 && tp->q_size == 0)
			pthread_cond_broadcast(&tp->done_cond);
		pthread_mutex_unlock(&tp->mtx);
	}
}

int	tpool_init(t_tpool *tp, int n_workers)
{
	int	i;

	memset(tp, 0, sizeof(*tp));
	if (n_workers < 1)
		n_workers = 1;
	tp->queue = (t_tpool_task *)malloc(sizeof(t_tpool_task) * TPOOL_QUEUE_CAP);
	if (!tp->queue)
		return (-1);
	tp->q_cap = TPOOL_QUEUE_CAP;
	tp->workers = (pthread_t *)malloc(sizeof(pthread_t) * n_workers);
	if (!tp->workers)
		return (free(tp->queue), tp->queue = NULL, -1);
	if (pthread_mutex_init(&tp->mtx, NULL) != 0)
		return (free(tp->workers), free(tp->queue), tp->workers = NULL, tp->queue = NULL, -1);
	if (pthread_cond_init(&tp->work_cond, NULL) != 0)
	{
		pthread_mutex_destroy(&tp->mtx);
		return (free(tp->workers), free(tp->queue), tp->workers = NULL, tp->queue = NULL, -1);
	}
	if (pthread_cond_init(&tp->done_cond, NULL) != 0)
	{
		pthread_cond_destroy(&tp->work_cond);
		pthread_mutex_destroy(&tp->mtx);
		return (free(tp->workers), free(tp->queue), tp->workers = NULL, tp->queue = NULL, -1);
	}
	i = 0;
	while (i < n_workers)
	{
		if (pthread_create(&tp->workers[i], NULL, tpool_worker, tp) != 0)
			break ;
		i++;
	}
	tp->n_workers = i;
	return (0);
}

int	tpool_submit(t_tpool *tp, t_task_fn fn, void *data)
{
	pthread_mutex_lock(&tp->mtx);
	if (tp->shutdown || tp->q_size >= tp->q_cap)
	{
		pthread_mutex_unlock(&tp->mtx);
		return (-1);
	}
	tp->queue[tp->q_tail].fn = fn;
	tp->queue[tp->q_tail].data = data;
	tp->q_tail = (tp->q_tail + 1) % tp->q_cap;
	tp->q_size++;
	pthread_cond_signal(&tp->work_cond);
	pthread_mutex_unlock(&tp->mtx);
	return (0);
}

void	tpool_wait(t_tpool *tp)
{
	pthread_mutex_lock(&tp->mtx);
	while (tp->q_size > 0 || tp->active > 0)
		pthread_cond_wait(&tp->done_cond, &tp->mtx);
	pthread_mutex_unlock(&tp->mtx);
}

void	tpool_destroy(t_tpool *tp)
{
	int	i;

	pthread_mutex_lock(&tp->mtx);
	tp->shutdown = 1;
	pthread_cond_broadcast(&tp->work_cond);
	pthread_mutex_unlock(&tp->mtx);
	i = 0;
	while (i < tp->n_workers)
	{
		pthread_join(tp->workers[i], NULL);
		i++;
	}
	pthread_cond_destroy(&tp->done_cond);
	pthread_cond_destroy(&tp->work_cond);
	pthread_mutex_destroy(&tp->mtx);
	free(tp->workers);
	free(tp->queue);
	memset(tp, 0, sizeof(*tp));
}
