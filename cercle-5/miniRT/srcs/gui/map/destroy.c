/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 08:42:18 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
/*
** Frees every map cache entry: its snap buffers, its scene (including BVH),
** and the path string.  Called from gui_destroy so all scene ownership is
** consolidated here rather than split between gui_destroy and main.c.
*/
void	map_manager_destroy(t_gui *gui)
{
	t_map_entry	*entry;
	t_map_entry	*next;

	entry = gui->map_info.head;
	while (entry)
	{
		next = entry->next;
		if (entry->snap)
		{
			scene_snap_free(entry->snap);
			free(entry->snap);
		}
		if (entry->scene)
			destroy_scene(entry->scene);
		free(entry->path);
		free(entry);
		entry = next;
	}
	gui->map_info.head = NULL;
	gui->map_info.current = NULL;
	gui->map_info.count = 0;
}
