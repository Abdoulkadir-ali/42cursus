/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/12 10:55:53 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "particles.h"
#include <stdlib.h>

/*
** Allocates all SoA arrays in one block via individual mallocs.
** Every array has n slots.  Returns NULL on any allocation failure.
*/
t_particle_soa	*particle_soa_alloc(size_t n)
{
	t_particle_soa	*soa;

	soa = ft_calloc(1, sizeof(*soa));
	if (!soa)
		return (NULL);
	soa->cap = n;
	soa->alive = 0;
	soa->px = ft_calloc(n, sizeof(double));
	soa->py = ft_calloc(n, sizeof(double));
	soa->pz = ft_calloc(n, sizeof(double));
	soa->vx = ft_calloc(n, sizeof(double));
	soa->vy = ft_calloc(n, sizeof(double));
	soa->vz = ft_calloc(n, sizeof(double));
	soa->age = ft_calloc(n, sizeof(double));
	soa->life = ft_calloc(n, sizeof(double));
	soa->temp = ft_calloc(n, sizeof(double));
	soa->size = ft_calloc(n, sizeof(double));
	if (!soa->px || !soa->py || !soa->pz
		|| !soa->vx || !soa->vy || !soa->vz
		|| !soa->age || !soa->life || !soa->temp || !soa->size)
	{
		particle_soa_free(soa);
		return (NULL);
	}
	return (soa);
}

void	particle_soa_free(t_particle_soa *soa)
{
	if (!soa)
		return ;
	free(soa->px);
	free(soa->py);
	free(soa->pz);
	free(soa->vx);
	free(soa->vy);
	free(soa->vz);
	free(soa->age);
	free(soa->life);
	free(soa->temp);
	free(soa->size);
	free(soa);
}

/*
** Appends an emitter to scene->emitters (DYNARRAY growth).
*/
bool	scene_add_emitter(t_scene *scene, t_emitter em)
{
	if (!DYNARRAY_ENSURE_INT(&scene->emitters, &scene->emitter_count,
			&scene->emitter_cap, sizeof(t_emitter)))
		return (false);
	em.active = true;
	em._accum = 0.0;
	scene->emitters[scene->emitter_count++] = em;
	return (true);
}
