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

/*
** Checks if a file has the .rt extension.
*/
static bool	is_rt_file(const char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (len < 4)
		return (false);
	return (ft_strcmp(filename + len - 3, ".rt") == 0);
}

/*
** Counts the number of .rt files in the maps directory.
*/
static int	count_maps(void)
{
	DIR				*dir;
	struct dirent	*entry;
	int				count;

	count = 0;
	dir = opendir("maps/rt");
	if (!dir)
		return (0);
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (entry->d_type == DT_REG && is_rt_file(entry->d_name))
			count++;
		entry = readdir(dir);
	}
	closedir(dir);
	return (count);
}

/*
** Fills the map_info structure with file names from the maps directory.
*/
static void	fill_map_list(t_gui *gui)
{
	DIR				*dir;
	struct dirent	*entry;
	dir = opendir("maps/rt");
	if (!dir)
		return ;
	gui->map_info.count = 0;
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (entry->d_type == DT_REG && is_rt_file(entry->d_name))
		{
            if (gui->map_info.count < 1024) // Sanity check if we can't easily pass cap
            {
			    gui->map_info.files[gui->map_info.count]
				    = ft_strjoin("maps/rt/", entry->d_name);
			    if (gui->map_info.files[gui->map_info.count])
				    gui->map_info.count++;
            }
		}
		entry = readdir(dir);
	}
	closedir(dir);
}

/*
** Sets the current map index matching the scene name.
*/
static void	set_current_index(t_gui *gui)
{
	int	i;

	gui->map_info.current_idx = 0;
	if (gui->scene && gui->scene->name)
	{
		i = 0;
		while (i < gui->map_info.count)
		{
			if (ft_strcmp(gui->scene->name, gui->map_info.files[i]) == 0)
			{
				gui->map_info.current_idx = i;
				break ;
			}
			i++;
		}
	}
}

/*
** Initializes the map switcher by scanning the maps directory.
*/
void	gui_map_switcher_init(t_gui *gui)
{
	int	count;

	count = count_maps();
	if (count == 0)
		return ;
	gui->map_info.files = ft_calloc(count + 1, sizeof(char *));
	if (!gui->map_info.files)
		return ;
	fill_map_list(gui);
	set_current_index(gui);
}

/*
** Resets camera view parameters from the scene camera.
*/
static void	reset_camera_view(t_gui *gui)
{
	t_vec3	f;

	if (!gui->cam_ctrl.camera)
		return ;
	f = gui->cam_ctrl.camera->transform.forward;
	gui->cam_ctrl.transform = gui->cam_ctrl.camera->transform;
	gui->cam_ctrl.target_rot.yaw = atan2(f.x, f.z);
	gui->cam_ctrl.target_rot.pitch = asin(f.y);
	gui->cam_ctrl.target_pos = gui->cam_ctrl.camera->transform.pos;
	gui->cam_ctrl.target_fov = gui->cam_ctrl.camera->fov;
}

/*
** Loads a new scene and BVH from the given path.
** Returns true on success, false otherwise.
*/
static bool	load_scene_and_bvh(t_gui *gui, const char *path)
{
	t_scene	*new_s;
	t_bvh	*new_b;

	ft_print_debug("Switching to map: %s\n", path);
	new_s = parse_file(path, gui->win.mlx);
	if (!new_s)
	{
		fprintf(stderr, "Error: Failed to load map %s\n", path);
		return (false);
	}
	new_b = bvh_create(new_s);
	if (!new_b)
	{
		fprintf(stderr, "Error: Failed to create BVH for %s\n", path);
		destroy_scene(new_s);
		return (false);
	}
	bvh_destroy(gui->bvh);
	destroy_scene(gui->scene);
	gui->scene = new_s;
	gui->bvh = new_b;
	return (true);
}

/*
** Switches to the next map in the list.
*/
void	gui_next_map(t_gui *gui)
{
	char	*path;

	if (gui->map_info.count == 0)
		return ;
	gui->map_info.current_idx = (gui->map_info.current_idx + 1)
		% gui->map_info.count;
	path = gui->map_info.files[gui->map_info.current_idx];
	if (load_scene_and_bvh(gui, path))
	{
		gui->cam_ctrl.camera = &gui->scene->camera;
		reset_camera_view(gui);
		gui->render.dirty = true;
	}
}
