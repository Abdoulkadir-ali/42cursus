/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 02:37:11 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

/**
 * @brief Bootstrap the application and enter the MLX event loop.
 * @param argc Number of command-line arguments.
 * @param argv Command-line argument array.
 * @return `0` on success, otherwise `1` for startup failures.
 */
int	main(int argc, char **argv)
{
	t_data		data;
	t_events	*events;

	if (argc != 2)
	{
		ft_putstr_fd("Error: Usage ./fdf <path/to/file.fdf>", 1);
		return (1);
	}
	XInitThreads();
	if (!init_data_and_window(&data, argc, argv))
		return (1);
	if (!init_camera_and_graphics(&data, argc, argv))
		return (1);
	if (!init_defaults_and_render(&data))
		return (1);
	if (!init_events_and_hooks(&data, &events))
		return (1);
	mlx_loop(data.mlx_ptr);
	return (0);
}
