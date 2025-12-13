/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 16:28:20 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/13 11:38:11 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

int	handle_horizontal(int keycode, t_events *events, int left)
{
	t_keys	*keyboard;

	(void)keycode;
	keyboard = &events->keys;
	if (left)
		keyboard->left = 1;
	else
		keyboard->right = 1;
	return (0);
}

static int	handle_flag(int keycode, t_events *events, int press)
{
	handle_button(keycode, events, press);
	return (0);
}

int	handle_press_flag(int keycode, t_events *events)
{
	return (handle_flag(keycode, events, 1));
}

int	handle_release_flag(int keycode, t_events *events)
{
	return (handle_flag(keycode, events, 0));
}
