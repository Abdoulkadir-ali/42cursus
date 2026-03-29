/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 16:20:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/29 11:04:35 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "mesh.h"
#include "debug.h"

static bool	load_by_ext(t_scene *scene, const char *path)
{
	const char	*ext;
	t_transform	t;

	ext = get_file_extension(path);
	if (ft_strcmp(ext, "rt") == 0)
		return (rt_load(scene, path));
	if (!load_mesh_file(scene, path))
		return (false);
	ft_memset(&t, 0, sizeof(t_transform));
	t.pos = vec3(0.0, 1.0, -4.0);
	t.forward = vec3(0.0, 0.0, 1.0);
	scene_apply_camera(scene, t, 70.0);
	return (true);
}
/*
** Activates a map entry, parsing and caching it on first access.
** If the entry already holds a scene, the cached scene is reused without
** reparsing.  The snap is taken exactly once — right after the first parse.
** Returns true on success, false if parsing or BVH creation failed.
*/
bool	map_load_entry(t_gui *gui, t_map_entry *entry)
{
	bool	newly_parsed;

	newly_parsed = (entry->scene == NULL);
	DBG_INFO_MSG(DBG_CH_PARSER,
		"map_load_entry: %s newly_parsed=%d\n",
		entry->path, newly_parsed);
	if (newly_parsed)
	{
		ft_print_debug("Loading map: %s\n", entry->path);
		entry->scene = create_scene(entry->path);
		if (!entry->scene)
		{
			fprintf(stderr, "Error: failed to load map %s\n", entry->path);
			return (false);
		}
		if (!load_by_ext(entry->scene, entry->path))
		{
			fprintf(stderr, "Error: failed to load map %s\n", entry->path);
			destroy_scene(entry->scene);
			entry->scene = NULL;
			return (false);
		}
	}
	else
		ft_print_debug("Using cached scene: %s\n", entry->path);
	pthread_rwlock_wrlock(&gui->scene_lock);
	gui->scene = entry->scene;
	pthread_rwlock_unlock(&gui->scene_lock);
	gui->map_info.current = entry;
	if (newly_parsed)
	{
		entry->snap = malloc(sizeof(t_scene_snap));
		if (entry->snap)
			scene_snapshot(entry->snap, gui);
	}
	return (true);
}

static void	*async_load_thread(void *arg)
{
	t_map_job	*job;
	t_map_entry	*entry;

	job = (t_map_job *)arg;
	entry = job->entry;
	if (!entry->scene)
	{
		ft_print_debug("Async loading map: %s\n", entry->path);
		entry->scene = create_scene(entry->path);
		if (entry->scene && !load_by_ext(entry->scene, entry->path))
		{
			destroy_scene(entry->scene);
			entry->scene = NULL;
		}
	}
	job->done = true;
	return (NULL);
}

void	map_load_async(t_gui *gui, t_map_entry *entry)
{
	if (gui->map_job.active)
		return ;
	if (entry->scene)
	{
		/* Already cached — swap immediately without a thread */
		pthread_rwlock_wrlock(&gui->scene_lock);
		gui->scene = entry->scene;
		pthread_rwlock_unlock(&gui->scene_lock);
		gui->map_info.current = entry;
		gui->cam_ctrl.camera = &gui->scene->camera;
		reset_camera_view(gui);
		clear_selection(gui);
		gui->render.dirty = true;
		return ;
	}
	gui->map_job.entry = entry;
	gui->map_job.done = false;
	gui->map_job.active = true;
	pthread_create(&gui->map_job.tid, NULL, async_load_thread, &gui->map_job);
}
