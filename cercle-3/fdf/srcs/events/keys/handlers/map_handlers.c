/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_handlers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 16:28:20 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/13 01:04:09 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"
#include <stdio.h>

int	handle_escape(int keycode, t_events *events)
{
	(void)keycode;
	DBG("handle_escape called\n");
	return (cleanup_and_exit(events));
}

int	handle_r(int keycode, t_events *events)
{
	(void)keycode;
	DBG("handle_r called\n");
	reset_view(events);
	reset_style(events->camera);
	return (1);
}

int	handle_n(int keycode, t_events *events)
{
	(void)keycode;
	DBG("handle_n called\n");
	cycle_map(&events->graphics->map_manager, &events->map);
	reset_view(events);
	// apply_map_style(events->map);
	return (1);
}

int	handle_s(int keycode, t_events *events)
{
	(void)keycode;
	DBG("handle_s called\n");
	cycle_gui_style(events->gui);
	return (1);
}

int	handle_a(int keycode, t_events *events)
{
	(void)keycode;
	DBG("handle_a called\n");
	events->render_mode = (events->render_mode + 1) % RENDER_MODE_COUNT;
	return (1);
}