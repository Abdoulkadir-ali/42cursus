/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   press.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:14:16 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/13 11:48:21 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

int	mouse_press(int button, int x, int y, t_events *events)
{
	handle_mouse_click(button, x, y, &events->mouse);
	if (handle_mouse_scroll(button, events))
		redraw(events);
	return (0);
}

int	mouse_release(int button, int x, int y, t_events *events)
{
	(void)x;
	(void)y;
	handle_mouse_release(button, &events->mouse);
	return (0);
}
