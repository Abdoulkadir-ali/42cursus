/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toggle_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 16:28:20 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/12 22:55:21 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"
#include <stdio.h>

int	handle_x(int keycode, t_events *events)
{
	(void)keycode;
	DBG("handle_x called\n");
	events->camera->use_z_divisor = !events->camera->use_z_divisor;
	return (1);
}

int	handle_i(int keycode, t_events *events)
{
	(void)keycode;
	DBG("handle_i called\n");
	events->camera->invert_movement = !events->camera->invert_movement;
	return (1);
}

int	handle_v(int keycode, t_events *events)
{
	(void)keycode;
	DBG("handle_v called\n");
	events->use_depth_culling = !events->use_depth_culling;
	return (1);
}

int	handle_g(int keycode, t_events *events)
{
	(void)keycode;
	DBG("handle_g called\n");
	events->fill_triangles = !events->fill_triangles;
	return (1);
}