/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 17:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/12 21:36:21 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

static void	free_map_files(t_events *events)
{
	int	i;

	if (events->graphics->map_manager.map_files)
	{
		i = 0;
		while (i < events->graphics->map_manager.count)
		{
			if (events->graphics->map_manager.map_files[i])
				free(events->graphics->map_manager.map_files[i]);
			i++;
		}
		free(events->graphics->map_manager.map_files);
	}
}

static void	free_cached_maps(t_events *events)
{
	int	i;

	if (events->graphics->map_manager.maps)
	{
		i = 0;
		while (i < events->graphics->map_manager.count)
		{
			if (events->graphics->map_manager.maps[i])
				free_map(events->graphics->map_manager.maps[i]);
			i++;
		}
		free(events->graphics->map_manager.maps);
	}
}

int	cleanup_and_exit(t_events *events)
{
	free_cached_maps(events);
	free_map_files(events);
	if (events->window->z_buffer)
		free(events->window->z_buffer);
	if (events->window->main_img.img)
		mlx_destroy_image(events->window->mlx_ptr, events->window->main_img.img);
	if (events->window->gui_img.img)
		mlx_destroy_image(events->window->mlx_ptr, events->window->gui_img.img);
	if (events->window->ptr)
		mlx_destroy_window(events->window->mlx_ptr, events->window->ptr);
	if (events->window->mlx_ptr)
	{
		mlx_destroy_display(events->window->mlx_ptr);
		free(events->window->mlx_ptr);
	}
	exit(0);
	return (0);
}
