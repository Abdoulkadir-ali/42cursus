/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toggle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/23 19:21:12 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

int	handle_t(int keycode, t_events *events)
{
	int	use_tesselation;

	(void)keycode;
	if (!events || !events->graphics)
		return (0);
	use_tesselation = !events->graphics->render_config.use_tesselation;
	events->graphics->render_config.use_tesselation = use_tesselation;
	return (1);
}

int	handle_j(int keycode, t_events *events)
{
	int	use_horizon_culling;

	(void)keycode;
	if (!events || !events->graphics)
		return (0);
	use_horizon_culling = !events->graphics->render_config.use_horizon_culling;
	events->graphics->render_config.use_horizon_culling = use_horizon_culling;
	return (1);
}
