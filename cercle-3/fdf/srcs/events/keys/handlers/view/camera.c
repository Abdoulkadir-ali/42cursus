/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 11:21:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/13 17:57:54 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

void	cycle_projection(t_events *events)
{
	events->camera->projection = (events->camera->projection + 1) % PROJ_COUNT;
}

void	reset_view(t_events *events)
{
	adjust_camera_to_map(events->camera_manager);
}

int	handle_p(int keycode, t_events *events)
{
	(void)keycode;
	cycle_projection(events);
	return (1);
}

int	process_movement(t_events *events)
{
	t_movement_ctx	ctx;

	if (!events || !events->camera)
		return (0);
	init_movement_ctx(&ctx, events);
	calculate_movement_vector(&ctx, events);
	if (ctx.v.x != 0 || ctx.v.y != 0)
	{
		apply_movement(&ctx, events);
		clamp_offset(events);
		return (1);
	}
	return (0);
}
