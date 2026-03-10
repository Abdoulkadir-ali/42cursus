/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bracket.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 03:24:09 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

/**
 * @brief Adjust the tessellation target-point budget with bracket-style keys.
 * @param keycode X11 keycode selecting the direction.
 * @param events Event context owning the graphics state.
 * @return `1` when processed, otherwise `0`.
 */
int	handle_bracket(int keycode, t_events *events)
{
	if (!events || !events->graphics)
		return (0);
	handle_tesselation_points(keycode, events->graphics);
	return (1);
}
