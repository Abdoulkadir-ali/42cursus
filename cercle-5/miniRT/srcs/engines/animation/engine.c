/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/05 13:46:43 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "animations.h"

char	*animation_mesh_name(t_mesh *m);

void	anim_engine_free(t_anim_engine *engine)
{
	if (!engine)
		return ;
	ft_print_debug("[ANIM] anim_engine_free: releasing %zu mesh indices\n",
		engine->mesh_count);
	free(engine->mesh_indices);
	engine->mesh_indices = NULL;
	engine->mesh_count = 0;
}

static void	tick_mesh(t_mesh *mesh, t_scene *scene, double dt)
{
	t_animation		*clip;
	t_mesh_anim		*ma;
	double			new_time;

	ma = &mesh->anim;
	if (ma->paused || ma->clip_idx < 0
		|| (size_t)ma->clip_idx >= scene->clip_count)
	{
		ft_print_debug("[ANIM] tick_mesh '%s': paused or invalid clip=%d\n",
			animation_mesh_name(mesh), ma->clip_idx);
		return ;
	}
	clip = &scene->clips[ma->clip_idx];
	new_time = ma->time + dt * ma->speed;
	if (clip->max_time > 0.0 && new_time > clip->max_time)
	{
		if (ma->looping)
			new_time = fmod(new_time, clip->max_time);
		else
			new_time = clip->max_time;
	}
	ma->time = new_time;
	clip->current_time = ma->time;
	mesh->bvh_dirty = true;
}

bool	update_animation_engine(t_scene *scene, t_anim_engine *engine,
			double dt)
{
	size_t	i;
	bool	updated;

	if (!scene || !engine || !engine->enabled || scene->clip_count == 0)
		return (false);
	if (engine->mesh_count == 0)
		anim_engine_rebuild_index(engine, scene);
	if (engine->mesh_count == 0)
		return (false);
	dt *= engine->time_scale;
	if (dt < 0.0)
		dt = 0.0;
	updated = false;
	i = -1;
	while (++i < engine->mesh_count)
	{
		if (engine->mesh_indices[i] < scene->mesh_count)
		{
			tick_mesh(&scene->meshes[engine->mesh_indices[i]], scene, dt);
			updated = true;
		}
	}
	return (updated);
}
