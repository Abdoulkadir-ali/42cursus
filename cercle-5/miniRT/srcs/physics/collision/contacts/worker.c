/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   worker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 14:15:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 15:30:26 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"
#include "scene.h"

/**
 * @brief Logic for a single physical collision job processed by a worker.
 */
void	run_contact_job(t_gen_job *j)
{
	t_gjk_shape	sa;
	t_dbvt_leaf	*leaf;

	if (!j->scene->static_bvh)
		return ;
	leaf = (t_dbvt_leaf *)j->arg;
	if (!leaf)
		return ;
	sa.data = leaf->shape;
	sa.support = leaf->support;
	sa.center = leaf->body->center;
	j->count = query_static_bvh(j->scene, j->scene->static_bvh->root,
			&sa, leaf->body, leaf->transform, j->out, j->count, j->max_c);
}

/**
 * @brief Thread entry point waiting for collision jobs.
 */
void	*pool_worker(void *arg)
{
	t_worker_arg	*wa;
	t_phys_pool		*pool;
	int				idx;

	wa = (t_worker_arg *)arg;
	pool = wa->scene->pool;
	idx = wa->index;
	while (1)
	{
		sem_wait(&pool->start[idx]);
		if (pool->shutdown)
		{
			sem_post(&pool->done[idx]);
			return (NULL);
		}
		run_contact_job(&pool->jobs[idx]);
		sem_post(&pool->done[idx]);
	}
}
