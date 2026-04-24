/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 11:06:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/05 18:12:11 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREAD_H
# define THREAD_H

# include <pthread.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include "time.h"
# include <stdatomic.h>


typedef void	*(*t_worker_func)(void *);

typedef struct s_thread_pool
{
	pthread_t		*threads;
	size_t			count;
	pthread_mutex_t	lock;
	pthread_cond_t	cond_work;
	pthread_cond_t	cond_done;
	t_worker_func	worker;
	void			*data;
	_Atomic size_t	running;
	char			_pad[56];
	size_t			generation;
	bool			stop;
	bool			initialized;
}	t_thread_pool;

/**
 * Lifecycle
 */
void	threads_init(t_thread_pool *pool);
void	threads_destroy(t_thread_pool *pool);

/**
 * Runs a worker function in parallel across multiple threads in the pool.
 */
void	parallel_run(t_thread_pool *pool, size_t count,
			t_worker_func worker, void *data);

#endif
