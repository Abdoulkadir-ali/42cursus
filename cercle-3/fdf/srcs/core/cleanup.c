/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 17:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 02:37:11 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

/**
 * @brief Release the array of discovered map file paths.
 * @param events Event context owning the map manager.
 */
static void	free_map_files(t_events *events)
{
	size_t	i;

	if (events->maps->map_files)
	{
		i = 0;
		while (i < events->maps->count)
		{
			if (events->maps->map_files[i])
				free(events->maps->map_files[i]);
			i++;
		}
		free(events->maps->map_files);
	}
}

/**
 * @brief Free every loaded map owned by the map manager.
 * @param events Event context owning the map manager.
 */
static void	free_cached_maps(t_events *events)
{
	size_t	i;

	if (events && events->maps)
	{
		i = 0;
		while (i < events->maps->count)
		{
			if (events->maps->maps[i])
				free_map(events->maps->maps[i]);
			i++;
		}
		free(events->maps->maps);
	}
}

/**
 * @brief Free the precomputed LOD maps owned by the graphics state.
 * @param graphics Graphics context owning the LOD maps.
 */
static void	free_lod_maps(t_graphics *graphics)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if (graphics->lod_maps[i])
			free_map(graphics->lod_maps[i]);
		i++;
	}
}

/**
 * @brief Destroy MLX images, the window, the display, and the z-buffer.
 * @param win Window structure owning the created images and z-buffer.
 * @param mlx MLX connection pointer.
 */
static void	destroy_window_and_images(t_window *win, void *mlx)
{
	if (win->z_buffer)
		free(win->z_buffer);
	if (win->main_img.img)
		mlx_destroy_image(mlx, win->main_img.img);
	if (win->gui_img.img)
		mlx_destroy_image(mlx, win->gui_img.img);
	if (win->ptr)
		mlx_destroy_window(mlx, win->ptr);
	if (mlx)
	{
		mlx_destroy_display(mlx);
		free(mlx);
	}
}

/**
 * @brief Release application resources and terminate the process.
 * @param events Event context owning the runtime subsystems.
 * @return Always `0`, though execution terminates via `exit(0)`.
 */
int	cleanup_and_exit(t_events *events)
{
	free_cached_maps(events);
	free_map_files(events);
	cleanup_cache(events->graphics);
	if (events->graphics->horizon_buffer)
		free(events->graphics->horizon_buffer);
	free_lod_maps(events->graphics);
	destroy_window_and_images(events->window, events->window->mlx_ptr);
	exit(0);
	return (0);
}
