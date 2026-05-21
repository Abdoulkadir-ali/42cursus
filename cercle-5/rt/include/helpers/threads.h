/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/08 19:38:05 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREADS_H
# define THREADS_H

# include <pthread.h>
# include <stdlib.h>
# include <string.h>

/*
** Generic persistent thread pool.
**
** Workers are created once at tpool_init() and sleep on a condition variable
** between batches.  This avoids pthread_create / pthread_join overhead on
** every hot-path invocation (e.g. every rendered frame).
**
** Usage pattern:
**   tpool_init(&tp, n_workers);
**   tpool_submit(&tp, my_fn, &args[i]);
**   tpool_wait(&tp);
**   tpool_destroy(&tp);
*/

# define TPOOL_QUEUE_CAP	4096
# define MAX_THREADS		32

typedef void			(*t_task_fn)(void *data);

typedef struct s_tpool_task
{
	t_task_fn	fn;
	void		*data;
}	t_tpool_task;

typedef struct s_tpool
{
	pthread_t		*workers;
	int				n_workers;
	t_tpool_task	*queue;
	int				q_cap;
	int				q_head;
	int				q_tail;
	int				q_size;
	int				active;
	int				shutdown;
	pthread_mutex_t	mtx;
	pthread_cond_t	work_cond;
	pthread_cond_t	done_cond;
}	t_tpool;

int		tpool_init(t_tpool *tp, int n_workers);
int		tpool_submit(t_tpool *tp, t_task_fn fn, void *data);
void	tpool_wait(t_tpool *tp);
void	tpool_destroy(t_tpool *tp);

#endif
