/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 21:15:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/13 19:23:12 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"
#include <stdio.h>

void	setup_hooks(t_events *events)
{
	mlx_hook(events->window->ptr, 17, 0, cleanup_and_exit, events);
	mlx_hook(events->window->ptr, 4, 1L << 2, mouse_press, events);
	mlx_hook(events->window->ptr, 5, 1L << 3, mouse_release, events);
	mlx_hook(events->window->ptr, 6, 1L << 6, mouse_move, events);
	mlx_hook(events->window->ptr, 2, 1L << 0, key_press, events);
	mlx_hook(events->window->ptr, 3, 1L << 1, key_release, events);
	mlx_loop_hook(events->window->mlx_ptr, loop_hook, events);
}