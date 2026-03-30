/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 16:20:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/30 20:35:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "editor.h"

static bool	map_load_internal(t_gui *gui, t_map_entry *entry)
{
	ft_print_debug("Loading map: %s\n", entry->path);
	entry->scene = parse_file(entry->path, gui->win.mlx);
	if (!entry->scene)
	{
		fprintf(stderr, "Error: failed to load map %s\n", entry->path);
		return (false);
	}
	return (true);
}

bool	map_load_entry(t_gui *gui, t_map_entry *entry)
{
	bool	newly_parsed;

	newly_parsed = (entry->scene == NULL);
	if (newly_parsed)
	{
		if (!map_load_internal(gui, entry))
			return (false);
	}
	else
		ft_print_debug("Using cached scene: %s\n", entry->path);
	gui->scene = entry->scene;
	gui->map_info.current = entry;
	if (newly_parsed)
		scene_snap_take(&entry->snap, gui);
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
		entry->scene = parse_file(entry->path, NULL);
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
		gui->scene = entry->scene;
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
