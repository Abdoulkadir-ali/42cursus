/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   current.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 16:20:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/11 16:20:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "editor.h"
#include "scene.h"

/*
** Finds the map entry matching the currently loaded scene's name and stores
** the scene pointer in that entry (transferring ownership to the cache).
** Takes the initial snapshot so scene_reset works from the first frame.
** Falls back to head if no match is found.
*/
void	set_current_entry(t_gui *gui)
{
	t_map_entry	*entry;

	entry = gui->map_info.head;
	gui->map_info.current = gui->map_info.head;
	while (entry)
	{
		if (gui->scene->name
			&& ft_strcmp(gui->scene->name, entry->path) == 0)
		{
			gui->map_info.current = entry;
			break ;
		}
		entry = entry->next;
	}
	if (gui->map_info.current)
	{
		gui->map_info.current->scene = gui->scene;
		scene_snap_take(&gui->map_info.current->snap, gui);
	}
}
