/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/14 09:41:18 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/**
 * @brief Dispatches contact generation jobs to the worker pool.
 */
static void	dispatch_jobs(t_scene *scene, t_physic_engine *engine,
				t_contact bufs[PHYS_NUM_TYPES][MAX_CONTACTS], size_t max_c)
{
	size_t	t;

	t = 0;
	while (t < PHYS_NUM_TYPES)
	{
		engine->pool.jobs[t] = (t_gen_job){engine, scene, bufs[t], max_c, 0, t};
		sem_post(&engine->pool.start[t++]);
	}
}

/**
 * @brief Collects contact points from the worker pool buffers.
 */
static size_t	collect_results(t_physic_engine *engine, t_contact *contacts,
				t_contact bufs[PHYS_NUM_TYPES][MAX_CONTACTS], size_t max_c)
{
	size_t	count;
	size_t	t;
	size_t	n;

	count = 0;
	t = 0;
	while (t < PHYS_NUM_TYPES)
	{
		sem_wait(&engine->pool.done[t]);
		n = engine->pool.jobs[t++].count;
		if (count + n > max_c)
			n = max_c - count;
		if (n > 0)
			ft_memcpy(&contacts[count], bufs[t - 1], sizeof(t_contact) * n);
		count += n;
	}
	return (count);
}

static void	zero_new_contacts(t_contact *c, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		c[i].accum_n = 0.0;
		c[i].accum_t = 0.0;
		c[i].lambda_pos = 0.0;
		i++;
	}
}

/**
 * @brief Main entry point for parallel contact generation.
 */
size_t	generate_contacts(t_scene *scene, t_physic_engine *engine,
		t_contact *contacts, size_t max_c)
{
	static t_contact	bufs[PHYS_NUM_TYPES][MAX_CONTACTS];
	size_t				count;

	engine->scene = scene;
	if (!engine->pool.initialized)
		init_phys_pool(engine);
	dispatch_jobs(scene, engine, bufs, max_c);
	count = collect_results(engine, contacts, bufs, max_c);
	zero_new_contacts(contacts, count);
	return (count);
}
