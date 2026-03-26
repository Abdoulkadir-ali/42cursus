/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 14:15:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 07:50:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"
#include "scene.h"

extern void	*pool_worker(void *arg);

void	phys_init_pool(t_scene *scene)
{
	int			i;
	t_phys_pool	*pool;

	pool = &scene->pool;
	i = -1;
	while (++i < PHYS_NUM_TYPES)
	{
		pool->args[i].scene = scene;
		pool->args[i].index = i;
		sem_init(&pool->start[i], 0, 0);
		sem_init(&pool->done[i], 0, 0);
		pthread_create(&pool->threads[i], NULL, pool_worker, &pool->args[i]);
	}
	pool->initialized = 1;
}

void	phys_destroy_pool(t_scene *scene)
{
	int			i;
	t_phys_pool	*pool;

	pool = &scene->pool;
	if (!pool->initialized)
		return ;
	pool->shutdown = 1;
	i = -1;
	while (++i < PHYS_NUM_TYPES)
		sem_post(&pool->start[i]);
	i = -1;
	while (++i < PHYS_NUM_TYPES)
	{
		pthread_join(pool->threads[i], NULL);
		sem_destroy(&pool->start[i]);
		sem_destroy(&pool->done[i]);
	}
	pool->initialized = 0;
}
