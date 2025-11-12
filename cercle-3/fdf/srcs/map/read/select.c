/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 16:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/12 17:51:17 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "camera.h"
#include "graphics.h"
#include <dirent.h>

static int	is_fdf_file(const char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 4)
		return (0);
	return (ft_strncmp(filename + len - 4, ".fdf", 4) == 0);
}

static int	count_fdf_files(DIR *dir)
{
	struct dirent	*entry;
	int				count;

	count = 0;
	entry = readdir(dir);
	while (entry)
	{
		if (is_fdf_file(entry->d_name))
			count++;
		entry = readdir(dir);
	}
	return (count);
}

static void	load_single_map(t_data *data, struct dirent *entry, int i)
{
	char	filepath[512];

	data->map_files[i] = malloc(ft_strlen(entry->d_name) + 1);
	ft_strcpy(data->map_files[i], entry->d_name);
	ft_strlcpy(filepath, "maps/test_maps/", sizeof(filepath));
	ft_strlcat(filepath, data->map_files[i], sizeof(filepath));
	data->maps[i] = load_map(filepath);
}

static void	load_map_files(t_data *data, DIR *dir, int count)
{
	struct dirent	*entry;
	int				i;

	i = 0;
	entry = readdir(dir);
	while (entry && i < count)
	{
		if (is_fdf_file(entry->d_name))
		{
			load_single_map(data, entry, i);
			i++;
		}
		entry = readdir(dir);
	}
}

void	init_map_list(t_data *data)
{
	DIR	*dir;
	int	count;

	dir = opendir("maps/test_maps");
	if (!dir)
	{
		data->map_files = NULL;
		data->maps = NULL;
		data->map_count = 0;
		return ;
	}
	count = count_fdf_files(dir);
	closedir(dir);
	data->map_files = malloc(sizeof(char *) * count);
	data->maps = malloc(sizeof(t_map *) * count);
	data->map_count = count;
	dir = opendir("maps/test_maps");
	load_map_files(data, dir, count);
	closedir(dir);
	data->current_map_index = 0;
}

void	cycle_map(t_data *data)
{
	t_camera_context	ctx;

	if (!data->maps || data->map_count == 0)
		return ;
	data->current_map_index = (data->current_map_index + 1) % data->map_count;
	data->map = data->maps[data->current_map_index];
	ctx.camera = &data->camera;
	ctx.map = data->map;
	ctx.window.width = data->win_width;
	ctx.window.height = data->win_height;
	adjust_camera_to_map(&ctx);
	apply_map_style(data);
	redraw(data);
}
