/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filled.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 18:43:49 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 03:24:09 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

/**
 * @brief Toggle filled rendering mode.
 * @param keycode Unused X11 keycode.
 * @param events Event context owning the graphics state.
 * @return Always `1`.
 */
int	handle_h(int keycode, t_events *events)
{
	(void)keycode;
	if (events->graphics->render_config.filled)
		events->graphics->render_config.filled = 0;
	else
		events->graphics->render_config.filled = 1;
	events->filled = events->graphics->render_config.filled;
	return (1);
}
