/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/24 14:30:23 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"
#include "raytracing.h"

static void	rebuild_sb_mesh_bvhs(t_scene *scene)
{
	size_t		i;
	t_soft_body	*sb;

	i = 0;
	while (i < scene->soft_body_count)
	{
		sb = &scene->soft_bodies[i++];
		if (sb->active && sb->mesh_idx < scene->mesh_count)
			mesh_build_bvh(&scene->meshes[sb->mesh_idx]);
	}
}

void	bvh_sync(t_scene *scene)
{
	t_bvh	*new_bvh;
	t_bvh	*old;

	if (!scene)
		return ;
	pthread_rwlock_wrlock(&scene->bvh_lock);
	rebuild_sb_mesh_bvhs(scene);
	pthread_rwlock_unlock(&scene->bvh_lock);
	new_bvh = bvh_create(scene);
	if (!new_bvh)
		return ;
	pthread_rwlock_wrlock(&scene->bvh_lock);
	old = scene->bvh;
	scene->bvh = new_bvh;
	pthread_rwlock_unlock(&scene->bvh_lock);
	bvh_destroy(old);
}

static uint32_t	hash_contact(t_physics_body *a, t_physics_body *b)
{
	uintptr_t	p1;
	uintptr_t	p2;

	p1 = (uintptr_t)a;
	p2 = (uintptr_t)b;
	if (p1 > p2)
	{
		p1 = (uintptr_t)b;
		p2 = (uintptr_t)a;
	}
	return ((uint32_t)(p1 ^ (p2 >> 4)));
}

void	persist_contacts(t_physic_engine *en, t_contact *new_c, size_t count)
{
	size_t		i;
	size_t		j;
	uint32_t	h;

	i = 0;
	while (i < count)
	{
		h = hash_contact(new_c[i].a, new_c[i].b);
		new_c[i].hash = h;
		j = 0;
		while (j < en->contact_count)
		{
			if (en->contacts[j].hash == h)
			{
				new_c[i].accum_n = en->contacts[j].accum_n * 0.9;
				new_c[i].accum_t = en->contacts[j].accum_t * 0.9;
				break ;
			}
			j++;
		}
		i++;
	}
	en->contact_count = count;
	ft_memcpy(en->contacts, new_c, sizeof(t_contact) * count);
}
