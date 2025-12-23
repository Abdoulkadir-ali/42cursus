/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filled.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 16:28:20 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/23 19:15:48 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

int	handle_g(int keycode, t_events *events)
{
	(void)keycode;
	events->filled = !events->filled;
	if (events->graphics)
		events->graphics->render_config.filled = events->filled;
	return (1);
}
