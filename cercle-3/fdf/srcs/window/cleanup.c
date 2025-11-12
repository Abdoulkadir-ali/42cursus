/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 17:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/12 21:01:52 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

static void	free_map_files(t_data *data)
{
	int	i;

	if (data->map_files)
	{
		i = 0;
		while (i < data->map_count)
		{
			if (data->map_files[i])
				free(data->map_files[i]);
			i++;
		}
		free(data->map_files);
	}
}

static void	free_cached_maps(t_data *data)
{
	int	i;

	if (data->maps)
	{
		i = 0;
		while (i < data->map_count)
		{
			if (data->maps[i])
				free_map(data->maps[i]);
			i++;
		}
		free(data->maps);
	}
}

int	cleanup_and_exit(t_data *data)
{
	free_cached_maps(data);
	free_map_files(data);
	if (data->window.z_buffer)
		free(data->window.z_buffer);
	if (data->window.main_img.img)
		mlx_destroy_image(data->mlx_ptr, data->window.main_img.img);
	if (data->window.gui_img.img)
		mlx_destroy_image(data->mlx_ptr, data->window.gui_img.img);
	if (data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	if (data->mlx_ptr)
	{
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
	}
	exit(0);
	return (0);
}
