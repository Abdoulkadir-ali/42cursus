/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 12:51:53 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/29 13:47:16 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"
#include "debug.h"

t_physics	*phys_create(struct s_scene *scene)
{
	t_physics	*p;

	DBG_INFO_MSG(DBG_CH_PHYSICS, "phys_create: start scene=%p\n",
		(void *)scene);
	p = malloc(sizeof(*p));
	if (!p)
	{
		DBG_ERR_MSG(DBG_CH_PHYSICS, "phys_create: alloc FAIL\n");
		return (NULL);
	}
	memset(p, 0, sizeof(*p));
	p->scene = scene;
	p->gravity = vec3(0.0, -9.81, 0.0);
	p->damping = GLOBAL_DAMPING;
	p->fixed_dt = 1.0 / 60.0;
	p->solver_iters = SOLVER_ITERATIONS;
	p->needs_bake = true;
	p->pool = NULL;
	DBG_INFO_MSG(DBG_CH_PHYSICS, "phys_create: OK p=%p gravity=-9.81\n",
		(void *)p);
	return (p);
}

void	phys_destroy(t_physics *phys)
{
	if (!phys)
		return ;
	if (phys->soa)
	{
		destroy_physics_soa(phys->soa);
		free(phys->soa);
	}
	free(phys);
}

static bool	ensure_soa(t_physics *phys)
{
	if (phys->soa)
		return (true);
	phys->soa = malloc(sizeof(t_physics_soa));
	if (!phys->soa)
		return (false);
	ft_memset(phys->soa, 0, sizeof(t_physics_soa));
	return (true);
}

void	phys_bake_scene(t_physics *phys, t_scene *scene)
{
	size_t	i;

	if (!phys || !scene)
		return ;
	phys->scene = scene;
	if (!ensure_soa(phys))
		return ;
	if (phys->soa->count > 0)
		destroy_physics_soa(phys->soa);
	if (scene->primitives.count > 0 && phys->soa->cap < scene->primitives.count)
		realloc_physics_soa(phys->soa, scene->primitives.count + 64);
	i = 0;
	while (i < scene->primitives.count)
	{
		soa_add_body(phys->soa, &scene->primitives, (int)i);
		i++;
	}
	phys->needs_bake = false;
}

