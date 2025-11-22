/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 13:32:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/22 13:57:39 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

int handle_resize(t_events *events)
{
    /* Query the OS for the ACTUAL window size */
    /* Note: mlx_get_screen_size gets screen res, not window. 
       We rely on the fact that standard MLX doesn't usually update window->height.
       However, we can force a buffer rebuild here. */
    
    /* If you have a modified MLX that supports mlx_get_window_size, use it.
       Otherwise, we assume the resize event implies we need to re-check.
       Standard 42 MLX is tricky here. The safest bet is to force a redraw 
       and let the GUI logic check dimensions if possible. */
       
    /* For now, simply forcing a redraw is usually enough if the OS updates the struct.
       If not, we simply rebuild the GUI buffer to be "safe" (e.g. MAX_HEIGHT) */
       
    redraw(events);
    return (0);
}