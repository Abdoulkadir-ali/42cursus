/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   level.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/23 19:15:37 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

int	handle_tesselation_up(int keycode, t_events *events)
{
	(void)keycode;
	if (events->graphics->tesselated_map)
	{
		free_map(events->graphics->tesselated_map);
		events->graphics->tesselated_map = NULL;
	}
	if (!events->graphics->render_config.use_tesselation)
		events->graphics->render_config.use_tesselation = 1;
	return (1);
}

int	handle_tesselation_down(int keycode, t_events *events)
{
	int	current;

	(void)keycode;
	if (!events || !events->graphics)
		return (0);
	current = events->graphics->render_config.tesselation_level;
	if (current > 1)
		events->graphics->render_config.tesselation_level--;
	if (events->graphics->tesselated_map)
	{
		free_map(events->graphics->tesselated_map);
		events->graphics->tesselated_map = NULL;
	}
	return (1);
}
