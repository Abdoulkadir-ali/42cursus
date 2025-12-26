/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/26 19:21:55 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

int	main(int argc, char **argv)
{
	t_data		data;
	t_events	*events;

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
