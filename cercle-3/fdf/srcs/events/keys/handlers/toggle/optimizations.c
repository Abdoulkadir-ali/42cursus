/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimizations.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 18:43:49 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/23 19:21:14 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

int	handle_manual_mode(int keycode, t_events *events)
{
	int	use_adaptive;

	(void)keycode;
	if (!events || !events->graphics)
		return (0);
	use_adaptive = !events->graphics->render_config.use_adaptive_logic;
	events->graphics->render_config.use_adaptive_logic = use_adaptive;
	if (!events->graphics->render_config.use_adaptive_logic)
	{
		events->graphics->render_config.tesselation_level = 1;
		events->graphics->render_config.lod_value = 1.0f;
		events->graphics->render_config.use_tesselation = 1;
	}
	return (1);
}
