/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 14:15:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 15:31:39 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"
#include "scene.h"

extern void	phys_init_pool(t_scene *scene);

/**
 * @brief Gathers contacts between dynamic actors and static environment.
 * Leverages the thread pool and Static BVH for O(log n) parallel resolution.
 */
int	gather_plane_contacts(t_scene *s, t_contact *contacts, int max_c)
{
	static t_contact	b[PHYS_NUM_TYPES][MAX_CONTACTS];
	int					c;
	int					t;
	int					n;

	if (!s->pool || !s->pool->initialized)
		phys_init_pool(s);
	c = 0;
	t = 3;
	while (++t < PHYS_NUM_TYPES)
	{
		s->pool->jobs[t] = (t_gen_job){s, b[t], max_c, 0, t, NULL};
		sem_post(&s->pool->start[t]);
	}
	t = 3;
	while (++t < PHYS_NUM_TYPES)
	{
		sem_wait(&s->pool->done[t]);
		n = s->pool->jobs[t].count;
		if (c + n > max_c)
			n = max_c - c;
		if (n > 0)
			memcpy(&contacts[c], b[t], sizeof(t_contact) * n);
		c += n;
	}
	return (c);
}
