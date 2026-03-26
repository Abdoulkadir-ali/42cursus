/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contacts.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 20:31:31 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 13:25:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

static t_phys_pool	g_pool;
static t_dbvt		g_dbvt;

static int	gather_dbvt_contacts(t_scene *s, t_contact *contacts, int max_c)
{
	t_body_pair	pairs[MAX_BODY_PAIRS];
	int			np;
	int			i;
	int			c;

	build_dbvt(s, &g_dbvt);
	np = dbvt_query_pairs(&g_dbvt, pairs, MAX_BODY_PAIRS);
	c = 0;
	i = 0;
	while (i < np && c < max_c)
	{
		c = narrow_dispatch(
			(t_dbvt_leaf *)pairs[i].a,
			(t_dbvt_leaf *)pairs[i].b,
			contacts, c);
		i++;
	}
	return (c);
}

static void	run_contact_job(t_gen_job *j)
{
	int	i;

	i = -1;
	if (j->type == 4)
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
	int	idx;

	idx = *(int *)arg;
	while (1)
	{
		sem_wait(&g_pool.start[idx]);
		if (g_pool.shutdown)
		{
			sem_post(&g_pool.done[idx]);
			return (NULL);
		}
		run_contact_job(&g_pool.jobs[idx]);
		sem_post(&g_pool.done[idx]);
	}
}

static void	init_pool(void)
{
	int	i;

	i = -1;
	while (++i < PHYS_NUM_TYPES)
	{
		g_pool.indices[i] = i;
		sem_init(&g_pool.start[i], 0, 0);
		sem_init(&g_pool.done[i], 0, 0);
		pthread_create(&g_pool.threads[i], NULL, pool_worker, &g_pool.indices[i]);
	}
	g_pool.initialized = 1;
}

static int	gather_plane_contacts(t_scene *s, t_contact *contacts, int max_c)
{
	static t_contact b[PHYS_NUM_TYPES][MAX_CONTACTS];
	int	c;
	int	t;
	int	n;

	if (!g_pool.initialized)
		init_pool();
	c = 0;
	t = 3;
	while (++t < PHYS_NUM_TYPES)
	{
		g_pool.jobs[t] = (t_gen_job){s, b[t], max_c, 0, t};
		sem_post(&g_pool.start[t]);
	}
	t = 3;
	while (++t < PHYS_NUM_TYPES)
	{
		sem_wait(&g_pool.done[t]);
		n = g_pool.jobs[t].count;
		if (c + n > max_c)
			n = max_c - c;
		if (n > 0)
			memcpy(&contacts[c], b[t], sizeof(t_contact) * n);
		c += n;
	}
	return (c);
}

/**
 * @brief Main contact generation entry point.
 * DBVT path: O(n log n) for all dynamic body pairs (sphere/box/capsule/cylinder).
 * Thread pool path: plane contacts for rect, tri, pyramid (GJK vs static planes).
 */
int	generate_contacts(t_scene *scene, t_contact *contacts, int max_c)
{
	int	c;
	int	n;

	c = gather_dbvt_contacts(scene, contacts, max_c);
	n = gather_plane_contacts(scene, &contacts[c], max_c - c);
	return (c + n);
}
