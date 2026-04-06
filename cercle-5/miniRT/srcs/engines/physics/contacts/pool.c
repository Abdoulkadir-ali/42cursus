/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 10:47:19 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/**
 * @brief Executes a contact generation job for a specific shape type.
 */
static void	run_contact_job(t_gen_job *job)
{
	size_t			i;
	t_contact_query	qu;

	i = 0;
	qu = init_contact_query(job->engine, job->out, job->count, job->max_c);
	while (job->type == 0 && i < job->scene->sphere_count)
		job->count = query_sphere(&qu, i++);
	while (job->type == 1 && i < job->scene->box_count)
		job->count = query_box(&qu, i++);
	while (job->type == 2 && i < job->scene->capsule_count)
		job->count = query_capsule(&qu, i++);
	while (job->type == 3 && i < job->scene->cylinder_count)
		job->count = query_cylinder(&qu, i++);
	while (job->type == 4 && i < job->scene->rect_count)
		job->count = query_rect(&qu, i++);
	while (job->type == 5 && i < job->scene->tri_count)
		job->count = query_tri(&qu, i++);
	while (job->type == 6 && i < job->scene->pyramid_count)
		job->count = query_pyramid(&qu, i++);
}

/**
 * @brief Worker thread routine for parallel collision detection.
 */
static void	*pool_worker(void *arg)
{
	size_t			idx;
	t_physic_engine	*engine;

	engine = ((t_worker_info *)arg)->engine;
	idx = ((t_worker_info *)arg)->idx;
	while (true)
	{
		sem_wait(&engine->pool.start[idx]);
		if (engine->pool.shutdown)
		{
			sem_post(&engine->pool.done[idx]);
			return (NULL);
		}
		run_contact_job(&engine->pool.jobs[idx]);
		sem_post(&engine->pool.done[idx]);
	}
	return (NULL);
}

/**
 * @brief Initializes the physics worker pool and its semaphores.
 */
void	init_phys_pool(t_physic_engine *engine)
{
	size_t	i;

	if (engine->pool.initialized)
		return ;
	i = 0;
	while (i < PHYS_NUM_TYPES)
	{
		engine->pool.worker_info[i].engine = engine;
		engine->pool.worker_info[i].idx = i;
		sem_init(&engine->pool.start[i], 0, 0);
		sem_init(&engine->pool.done[i], 0, 0);
		pthread_create(&engine->pool.threads[i], NULL,
			pool_worker, &engine->pool.worker_info[i]);
		i++;
	}
	engine->pool.initialized = true;
}
