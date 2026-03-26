/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contacts.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 20:31:31 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 14:15:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"
#include <unistd.h>

static int	process_pair(t_scene *s, t_body_pair *p, t_contact *contacts, int c, int max_c)
{
	t_shape_pair	sp[MAX_BODY_PAIRS];
	int				ns;
	int				i;

	if (!p->a->is_compound && !p->b->is_compound)
	{
		return (narrow_dispatch_body_pair(p, contacts, c));
	}
	ns = midphase(p, 1, sp, MAX_BODY_PAIRS);
	i = 0;
	while (i < ns && c < max_c)
	{
		c = narrow_dispatch_shape_pair(&sp[i], contacts, c);
		i++;
	}
	return (c);
}

static int	gather_dbvt_contacts(t_scene *s, t_contact *contacts, int max_c)
{
	t_body_pair	pairs[MAX_BODY_PAIRS];
	int			np;
	int			i;
	int			c;

	build_dbvt(s, &s->dbvt);
	np = dbvt_query_pairs(&s->dbvt, pairs, MAX_BODY_PAIRS);
	c = 0;
	i = 0;
	while (i < np && c < max_c)
	{
		c = process_pair(s, &pairs[i], contacts, c, max_c);
		i++;
	}
	return (c);
}

static void	run_contact_job(t_gen_job *j)
{
	t_gjk_shape	sa;
	t_dbvt_leaf	*leaf;

	if (!j->scene->static_bvh)
		return ;
	/* Here we'd iterate over dynamic bodies assigned to the job.
	** For now, we perform a refined query for the specific type assigned. */
	/* (Simplified for Step 42 but keeping the acceleration logic) */
	leaf = (t_dbvt_leaf *)j->arg; /* Assume arg is the dynamic source */
	if (!leaf) return ;
	
	sa.data = leaf->shape;
	sa.support = leaf->support;
	sa.center = leaf->body->center;
	j->count = query_static_bvh(j->scene, j->scene->static_bvh->root, 
			&sa, leaf->body, &leaf->body->transform, j->out, j->count, j->max_c);
}

static void	*pool_worker(void *arg)
{
	t_worker_arg	*wa;
	t_phys_pool		*pool;
	int				idx;

	wa = (t_worker_arg *)arg;
	pool = &wa->scene->pool;
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

/**
 * @brief Shuts down and cleans up the scene's physics thread pool.
 */
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

static int	gather_plane_contacts(t_scene *s, t_contact *contacts, int max_c)
{
	static t_contact b[PHYS_NUM_TYPES][MAX_CONTACTS];
	int	c;
	int	t;
	int	n;

	if (!s->pool.initialized)
		phys_init_pool(s);
	c = 0;
	t = 3;
	while (++t < PHYS_NUM_TYPES)
	{
		s->pool.jobs[t] = (t_gen_job){s, b[t], max_c, 0, t};
		sem_post(&s->pool.start[t]);
	}
	t = 3;
	while (++t < PHYS_NUM_TYPES)
	{
		sem_wait(&s->pool.done[t]);
		n = s->pool.jobs[t].count;
		if (c + n > max_c)
			n = max_c - c;
		if (n > 0)
			memcpy(&contacts[c], b[t], sizeof(t_contact) * n);
		c += n;
	}
	return (c);
}

int	generate_contacts(t_scene *scene, t_contact *contacts, int max_c)
{
	int	c;
	int	n;

	c = gather_dbvt_contacts(scene, contacts, max_c);
	n = gather_plane_contacts(scene, &contacts[c], max_c - c);
	return (c + n);
}
