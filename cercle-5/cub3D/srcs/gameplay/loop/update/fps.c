/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 09:31:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/29 09:31:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gameplay.h"

void	update_fps(t_world *world, int elapsed_us)
{
	float	curr_fps;

	if (elapsed_us > 0)
	{
		curr_fps = 1000000.0f / (float)elapsed_us;
		if (world->fps == 0)
			world->fps = curr_fps;
		else
			world->fps = world->fps * 0.9f + curr_fps * 0.1f;
		world->frame_time_ms = (float)elapsed_us / 1000.0f;
	}
}
