/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   soft_body_life.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/14 10:50:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"
#include <stdlib.h>

bool	soft_body_build(t_soft_body *sb, t_mesh *mesh, t_sb_params p)
{
	size_t	p_count;

	if (!mesh || !mesh->vertices || !mesh->triangles)
		return (false);
	p_count = mesh->vertex_count;
	if (p_count > MAX_SB_PARTICLES)
		p_count = MAX_SB_PARTICLES;
	sb->particles = ft_calloc(p_count, sizeof(t_sb_particle));
	sb->springs = ft_calloc(MAX_SB_SPRINGS, sizeof(t_sb_spring));
	if (!sb->particles || !sb->springs)
	{
		free(sb->particles);
		free(sb->springs);
		return (false);
	}
	sb->particle_count = p_count;
	fill_particles(sb->particles, mesh, p_count, p.offset);
	soft_body_build_springs(sb, mesh, p_count);
	sb->mesh_idx = p.mesh_idx;
	sb->stiffness = p.stiffness;
	sb->damping = p.damping;
	sb->active = true;
	return (true);
}

static bool	realloc_sb(t_scene *scene)
{
	size_t		cap;
	t_soft_body	*arr;

	cap = 4;
	if (scene->soft_body_cap)
		cap = scene->soft_body_cap * 2;
	arr = ft_calloc(cap, sizeof(t_soft_body));
	if (!arr)
		return (false);
	if (scene->soft_bodies)
	{
		ft_memcpy(arr, scene->soft_bodies,
			scene->soft_body_count * sizeof(t_soft_body));
		free(scene->soft_bodies);
	}
	scene->soft_bodies = arr;
	scene->soft_body_cap = cap;
	return (true);
}

bool	scene_build_soft_body(t_scene *scene, t_sb_params p)
{
	t_soft_body	*sb;

	if (p.mesh_idx >= scene->mesh_count)
		return (false);
	if (scene->soft_body_count >= scene->soft_body_cap)
	{
		if (!realloc_sb(scene))
			return (false);
	}
	sb = &scene->soft_bodies[scene->soft_body_count++];
	ft_memset(sb, 0, sizeof(*sb));
	return (soft_body_build(sb, &scene->meshes[p.mesh_idx], p));
}

static void	jiggle_p(t_sb_particle *p, size_t j)
{
	double	rand_x;
	double	rand_y;
	double	rand_z;
	double	base;

	if (p->inv_mass <= 0.0)
		return ;
	base = 5.0 + (j % 7) * 0.5;
	rand_x = ((double)(j % 5) - 2.0) * base * 0.3;
	rand_y = base;
	rand_z = ((double)(j % 3) - 1.0) * base * 0.3;
	p->vel = vec3_add(p->vel, vec3(rand_x, rand_y, rand_z));
}

void	soft_body_jiggle(t_scene *scene)
{
	size_t			i;
	size_t			j;
	t_soft_body		*sb;

	i = -1;
	while (++i < scene->soft_body_count)
	{
		sb = &scene->soft_bodies[i];
		if (!sb->active)
			continue ;
		j = -1;
		while (++j < sb->particle_count)
			jiggle_p(&sb->particles[j], j);
	}
}
