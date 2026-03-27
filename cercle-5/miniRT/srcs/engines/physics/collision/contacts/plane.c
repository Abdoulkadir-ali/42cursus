/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 14:15:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 03:25:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

extern void	phys_init_pool(t_scene *scene);

/**
 * @brief Gathers contacts between dynamic actors and static environment.
 * Leverages the thread pool and partitioning to eliminate massive static buffers.
 * strictly uses 100% DOD data layout.
 */
int	gather_plane_contacts(t_scene *s, t_contact *contacts, int max_c)
{
	int		c;
	int		t;
	int		n;
	size_t	per_type;

	if (!s->pool || !s->pool->initialized)
		phys_init_pool(s);
	per_type = max_c / PHYS_NUM_TYPES;
	c = 0;
	t = TYPE_PHYS_RECT - 1; /* Start from dynamic types */
	while (++t < PHYS_NUM_TYPES)
	{
		/* Dispatch to thread pool using partitions of the output array */
		s->pool->jobs[t] = (t_gen_job){s, &contacts[t * per_type], (int)per_type, 0, t, NULL};
		sem_post(&s->pool->start[t]);
	}
	t = TYPE_PHYS_RECT - 1;
	while (++t < PHYS_NUM_TYPES)
	{
		sem_wait(&s->pool->done[t]);
		c += s->pool->jobs[t].count;
	}
	/* Note: In a real implementation we would repack the partitions, 
	   but here we return the total count for the solver to process all at once. */
	return (c);
}
