/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filled.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 18:43:49 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/25 21:04:32 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

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
