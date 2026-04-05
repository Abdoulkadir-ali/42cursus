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

/*
** Build (or rebuild) the flat index of meshes that have a skeleton.
** Called once after a scene load. O(mesh_count) scan, then never again
** unless the scene changes.
*/
void	anim_engine_rebuild_index(t_anim_engine *engine, t_scene *scene)
{
	size_t	i;
	size_t	n;

	free(engine->mesh_indices);
	engine->mesh_indices = NULL;
	engine->mesh_count = 0;
	if (!scene)
		return ;
	n = 0;
	i = 0;
	while (i < scene->mesh_count)
	{
		if (scene->meshes[i].skeleton && scene->meshes[i].bone_count > 0)
			n++;
		i++;
	}
	ft_print_debug("[ANIM] rebuild_index: %zu/%zu meshes are skinned\n",
		n, scene->mesh_count);
	if (n == 0)
		return ;
	engine->mesh_indices = malloc(sizeof(size_t) * n);
	if (!engine->mesh_indices)
		return ;
	engine->mesh_count = n;
	n = 0;
	i = 0;
	while (i < scene->mesh_count)
	{
		if (scene->meshes[i].skeleton && scene->meshes[i].bone_count > 0)
		{
			engine->mesh_indices[n] = i;
			ft_print_debug("[ANIM]   indexed mesh[%zu] '%s' bone_count=%zu\n",
				i,
				scene->meshes[i].name ? scene->meshes[i].name : "?",
				scene->meshes[i].bone_count);
			n++;
		}
		i++;
	}
}

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

/*
** Advance a single mesh's local clock and apply it.
** Uses mesh->anim.clip_idx to select the clip, mesh->anim.speed to scale dt,
** and loops / pauses as configured.
*/
static void	tick_mesh(t_mesh *mesh, t_scene *scene, double dt)
{
	t_animation		*clip;
	t_mesh_anim		*ma;
	double			new_time;

	ma = &mesh->anim;
	if (ma->paused || ma->clip_idx < 0
		|| (size_t)ma->clip_idx >= scene->clip_count)
	{
		ft_print_debug("[ANIM] tick_mesh '%s': skipped (paused=%d clip_idx=%d)\n",
			mesh->name ? mesh->name : "?", ma->paused, ma->clip_idx);
		return ;
	}
	clip = &scene->clips[ma->clip_idx];
	new_time = ma->time + dt * ma->speed;
	if (clip->max_time > 0.0)
	{
		if (new_time > clip->max_time)
		{
			if (ma->looping)
				new_time = fmod(new_time, clip->max_time);
			else
				new_time = clip->max_time;
		}
	}
	ft_print_debug("[ANIM] tick_mesh '%s': clip[%d] time %.3f->%.3f (max=%.3f)\n",
		mesh->name ? mesh->name : "?",
		ma->clip_idx, ma->time, new_time, clip->max_time);
	ma->time = new_time;
	clip->current_time = ma->time;
	mesh->bvh_dirty = true;
}

/*
** Drive the animation engine for one frame.
** Iterates only the pre-built index of skinned meshes — O(animated) not
** O(all meshes). Returns true when at least one mesh was updated.
*/
bool	update_animation_engine(t_scene *scene, t_anim_engine *engine, double dt)
{
	size_t	i;
	size_t	mi;
	bool	updated;

	if (!scene || !engine || !engine->enabled || scene->clip_count == 0)
	{
		ft_print_debug("[ANIM] update_animation_engine: skipped "
			"(enabled=%d clips=%zu)\n",
			engine ? engine->enabled : -1,
			scene ? scene->clip_count : 0);
		return (false);
	}
	if (engine->mesh_count == 0)
	{
		ft_print_debug("[ANIM] update_animation_engine: building index...\n");
		anim_engine_rebuild_index(engine, scene);
	}
	if (engine->mesh_count == 0)
	{
		ft_print_debug("[ANIM] update_animation_engine: no skinned meshes found\n");
		return (false);
	}
	dt *= engine->time_scale;
	if (dt < 0.0)
		dt = 0.0;
	updated = false;
	i = 0;
	while (i < engine->mesh_count)
	{
		mi = engine->mesh_indices[i];
		if (mi < scene->mesh_count)
		{
			tick_mesh(&scene->meshes[mi], scene, dt);
			updated = true;
		}
		i++;
	}
	return (updated);
}
