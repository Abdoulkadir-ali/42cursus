/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_thread.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 11:05:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/04 11:45:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_THREAD_H
# define T_THREAD_H

typedef void	*(*t_worker_func)(void *);

typedef struct s_thread_pool
{
	void			*threads;
	size_t			count;
	char			lock[64];
	char			cond_work[48];
	char			cond_done[48];
	t_worker_func	worker;
	void			*data;
	_Atomic size_t	running;
	char			_pad[56];
	int				stop;
	int				initialized;
}	t_thread_pool;

#endif
