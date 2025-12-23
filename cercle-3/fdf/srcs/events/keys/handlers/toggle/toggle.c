/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toggle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 16:28:20 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/13 11:40:07 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"



int	handle_i(int keycode, t_events *events)
{
	(void)keycode;
	events->camera->invert_movement = !events->camera->invert_movement;
	return (1);
}

int	handle_v(int keycode, t_events *events)
{
	(void)keycode;
	events->use_depth_culling = !events->use_depth_culling;
	return (1);
}

int	handle_g(int keycode, t_events *events)
{
	(void)keycode;
	events->filled = !events->filled;
	if (events->graphics)
		events->graphics->render_config.filled = events->filled;
	return (1);
}
