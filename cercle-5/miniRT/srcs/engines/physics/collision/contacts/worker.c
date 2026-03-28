/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   worker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 14:15:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 10:27:48 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/**
 * @brief Logic for a single physical collision job processed by a worker.
 */
void	run_contact_job(t_gen_job *j)
{
	t_gjk_shape	sa;
	t_dbvt_leaf	*leaf;
	int			i;

	if (!j->scene || !j->scene->static_bvh)
		return ;
	if (j->arg)
	{
		leaf = (t_dbvt_leaf *)j->arg;
		sa.idx = leaf->shape_idx;
		sa.scene = j->scene;
		sa.support = leaf->support;
		sa.center = leaf->body->center;
		j->count = query_static_bvh(j->scene, j->scene->static_bvh->root,
				&sa, leaf->body, leaf->transform, j->out, j->count, j->max_c);
		return ;
	}
	i = -1;
	while (++i < j->scene->dbvt.leaf_count)
	{
		leaf = &j->scene->dbvt.leaves[i];
		if (leaf->type == (t_phys_type)j->type)
		{
			sa.idx = leaf->shape_idx;
			sa.scene = j->scene;
			sa.support = leaf->support;
			sa.center = leaf->body->center;
			j->count = query_static_bvh(j->scene, j->scene->static_bvh->root,
					&sa, leaf->body, leaf->transform, j->out, j->count, j->max_c);
		}
	}
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
