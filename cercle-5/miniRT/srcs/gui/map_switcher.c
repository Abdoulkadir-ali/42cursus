/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_switcher.c                                     :+:      :+:    :+:   */
/*                                                                            */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 23:45:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/07 23:45:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

static bool	is_rt_file(const char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (len < 4)
		return (false);
	return (ft_strcmp(filename + len - 3, ".rt") == 0);
}

void	gui_map_switcher_init(t_gui *gui)
{
	DIR				*dir;
	struct dirent	*entry;
	int				count;

	count = 0;
	dir = opendir("maps");
	if (!dir)
		return ;
	while ((entry = readdir(dir)) != NULL)
	{
		if (entry->d_type == DT_REG && is_rt_file(entry->d_name))
			count++;
	}
	closedir(dir);
	if (count == 0)
		return ;
	gui->maps = ft_calloc(count + 1, sizeof(char *));
	if (!gui->maps)
		return ;
	dir = opendir("maps");
	if (!dir)
		return ;
	gui->map_count = 0;
	while ((entry = readdir(dir)) != NULL)
	{
		if (entry->d_type == DT_REG && is_rt_file(entry->d_name))
		{
			gui->maps[gui->map_count] = ft_strjoin("", entry->d_name);
			if (gui->maps[gui->map_count])
				gui->map_count++;
		}
	}
	closedir(dir);
	// Set current map index based on current scene name if possible
	gui->current_map_idx = 0;
	if (gui->scene && gui->scene->name)
	{
		for (int i = 0; i < gui->map_count; i++)
		{
			if (ft_strcmp(gui->scene->name, gui->maps[i]) == 0)
			{
				gui->current_map_idx = i;
				break ;
			}
		}
	}
}

static void	reset_camera_view(t_gui *gui)
{
	t_vec3 f = gui->camera->transform.forward;
	gui->rotation.yaw = atan2(f.x, f.z);
	gui->rotation.pitch = asin(f.y);
	gui->target_rotation = gui->rotation;
	gui->target_position = gui->camera->transform.pos;
	gui->target_fov = gui->camera->fov;
}

void	gui_next_map(t_gui *gui)
{
	t_scene	*new_scene;
	t_bvh	*new_bvh;
	char	*path;

	if (gui->map_count == 0)
		return ;
	gui->current_map_idx = (gui->current_map_idx + 1) % gui->map_count;
	path = gui->maps[gui->current_map_idx];
	printf("Switching to map: %s\n", path);
	new_scene = parse_file(path);
	if (!new_scene)
	{
		printf("Error: Failed to load map %s\n", path);
		return ;
	}
	new_bvh = bvh_create(new_scene);
	if (!new_bvh)
	{
		printf("Error: Failed to create BVH for %s\n", path);
		destroy_scene(new_scene);
		return ;
	}
	// Switch references
	bvh_destroy(gui->bvh);
	destroy_scene(gui->scene);
	gui->scene = new_scene;
	gui->bvh = new_bvh;
	gui->camera = &new_scene->camera;
	reset_camera_view(gui);
	gui->dirty = true;
}
