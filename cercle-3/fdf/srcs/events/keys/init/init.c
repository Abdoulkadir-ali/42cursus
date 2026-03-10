/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   XK_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:14:11 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/12 16:33:45 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

/**
 * @brief Initialize both key press and key release dispatch tables.
 * @param key_maps Key-map structure to populate.
 */
void	init_key_actions(t_key_maps *key_maps)
{
	set_key_actions(key_maps);
	set_key_releases(key_maps);
}

/**
 * @brief Dispatch a key press through the action lookup table.
 * @param keycode X11 keycode to process.
 * @param events Event context owning the key maps.
 * @return Handler result, usually whether an immediate redraw is needed.
 */
int	key_press(int keycode, t_events *events)
{
	t_key_action	action;
	int				redraw_needed;

	if (keycode >= 0 && keycode < KEY_MAP_SIZE)
	{
		action = events->key_maps.key_actions[keycode];
		if (action)
		{
			redraw_needed = action(keycode, events);
			if (redraw_needed)
				redraw(events);
			return (redraw_needed);
		}
	}
	return (0);
}

/**
 * @brief Dispatch a key release through the release lookup table.
 * @param keycode X11 keycode to process.
 * @param events Event context owning the key maps.
 * @return Handler result, or `0` when no release action exists.
 */
int	key_release(int keycode, t_events *events)
{
	t_key_action	action;

	if (keycode >= 0 && keycode < KEY_MAP_SIZE)
	{
		action = events->key_maps.key_releases[keycode];
		if (action)
			return (action(keycode, events));
	}
	return (0);
}
