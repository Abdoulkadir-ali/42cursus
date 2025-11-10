/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 16:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/10 17:47:43 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <dirent.h>
#include <stdio.h>

static int	is_fdf_file(const char *filename)
{
	int	len;

	len = strlen(filename);
	if (len < 4)
		return (0);
	return (strcmp(filename + len - 4, ".fdf") == 0);
}

void	init_map_list(t_data *data)
{
	DIR				*dir;
	struct dirent	*entry;
	int				count;
	int				i;
	char			filepath[512];

	dir = opendir("maps/test_maps");
	if (!dir)
	{
		data->map_files = NULL;
		data->maps = NULL;
		data->map_count = 0;
		return ;
	}
	count = 0;
	while ((entry = readdir(dir)) != NULL)
		if (is_fdf_file(entry->d_name))
			count++;
	closedir(dir);
	data->map_files = malloc(sizeof(char *) * count);
	data->maps = malloc(sizeof(t_map *) * count);
	data->map_count = count;
	dir = opendir("maps/test_maps");
	i = 0;
	while ((entry = readdir(dir)) != NULL && i < count)
	{
		if (is_fdf_file(entry->d_name))
		{
			data->map_files[i] = malloc(strlen(entry->d_name) + 1);
			strcpy(data->map_files[i], entry->d_name);
			snprintf(filepath, sizeof(filepath), "maps/test_maps/%s",
				data->map_files[i]);
			data->maps[i] = load_map(filepath);
			i++;
		}
	}
	closedir(dir);
	data->current_map_index = 0;
}

void	cycle_map(t_data *data)
{
	if (!data->maps || data->map_count == 0)
		return ;
	data->current_map_index = (data->current_map_index + 1) % data->map_count;
	data->map = data->maps[data->current_map_index];
	adjust_camera_to_map(data);
	apply_map_style(data);
	redraw(data);
}
