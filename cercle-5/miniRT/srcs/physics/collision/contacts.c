/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contacts.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 20:31:31 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 09:30:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* *****************:********************************************************* */

#include "physics.h"

static void	run_contact_job(t_gen_job *j)
{
	int	i = -1;
	if (j->type == 0)
		while (++i < j->scene->sphere_count)
			j->count = query_sphere(j->scene, i, j->out, j->count, j->max_c);
	else if (j->type == 1)
		while (++i < j->scene->box_count)
			j->count = query_box(j->scene, i, j->out, j->count, j->max_c);
	else if (j->type == 2)
		while (++i < j->scene->capsule_count)
			j->count = query_capsule(j->scene, i, j->out, j->count, j->max_c);
	else if (j->type == 3)
		while (++i < j->scene->cylinder_count)
			j->count = query_cylinder(j->scene, i, j->out, j->count, j->max_c);
	else if (j->type == 4)
		while (++i < j->scene->rect_count)
			j->count = query_rect(j->scene, i, j->out, j->count, j->max_c);
	else if (j->type == 5)
		while (++i < j->scene->tri_count)
			j->count = query_tri(j->scene, i, j->out, j->count, j->max_c);
	else
		while (++i < j->scene->pyramid_count)
			j->count = query_pyramid(j->scene, i, j->out, j->count, j->max_c);
}

static void	*pool_worker(void *arg)
{
	int	idx = *(int *)arg;
	while (1)
	{
		sem_wait(&g_pool.start[idx]);
		if (g_pool.shutdown) { sem_post(&g_pool.done[idx]); return (NULL); }
		run_contact_job(&g_pool.jobs[idx]);
		sem_post(&g_pool.done[idx]);
	}
}

static void	init_pool(void)
{
	int	i = -1;
	while (++i < PHYS_NUM_TYPES)
	{
		g_pool.indices[i] = i;
		sem_init(&g_pool.start[i], 0, 0);
		sem_init(&g_pool.done[i], 0, 0);
		pthread_create(&g_pool.threads[i], NULL, pool_worker, &g_pool.indices[i]);
	}
	g_pool.initialized = 1;
}

int	generate_contacts(t_scene *scene, t_contact *contacts, int max_c)
{
	static t_contact b[PHYS_NUM_TYPES][MAX_CONTACTS];
	int c = 0; int t = -1; int n;
	if (!g_pool.initialized) init_pool();
	while (++t < PHYS_NUM_TYPES)
	{
		g_pool.jobs[t] = (t_gen_job){scene, b[t], max_c, 0, t};
		sem_post(&g_pool.start[t]);
	}
	t = -1;
	while (++t < PHYS_NUM_TYPES)
	{
		sem_wait(&g_pool.done[t]);
		n = g_pool.jobs[t].count;
		if (c + n > max_c) n = max_c - c;
		if (n > 0) memcpy(&contacts[c], b[t], sizeof(t_contact) * n);
		c += n;
	}
	return (c);
}
