/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 18:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 17:22:05 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

int	phys_body_for_sphere(t_phys_world *w, int sphere_idx)
{
	int	i;

	i = 0;
	while (i < w->n)
	{
		if (w->bodies[i].sphere_idx == sphere_idx)
			return (i);
		i++;
	}
	return (-1);
}

int	phys_add_body(t_phys_world *w, int sphere_idx, float mass,
				float restitution, t_vec3 vel)
{
	t_body	*tmp;
	t_body	*b;
	int	cap;

	if (w->n + 1 > w->cap)
	{
		cap = w->cap ? w->cap * 2 : 64;
		tmp = (t_body *)realloc(w->bodies, sizeof(t_body) * cap);
		if (!tmp)
			return (-1);
		w->bodies = tmp;
		w->cap = cap;
	}
	b = &w->bodies[w->n++];
	b->sphere_idx = sphere_idx;
	b->mass = mass;
	b->inv_mass = (mass > 0.0f) ? 1.0f / mass : 0.0f;
	b->restitution = restitution;
	b->vel = vel;
	b->acc = v3(0, 0, 0);
	b->active = 1;
	b->is_static = (mass <= 0.0f);
	b->radius_cache = 1.0f;
	b->pos = v3(0, 0, 0);
	b->temp_ambient = 295.0f;
	b->temperature = 295.0f;
	return (w->n - 1);
}
