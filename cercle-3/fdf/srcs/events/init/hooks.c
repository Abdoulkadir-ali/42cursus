/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 03:23:24 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

/**
 * @brief Register all window, mouse, keyboard, resize, and loop hooks.
 * @param e Event context owning the active window.
 */
void	setup_hooks(t_events *e)
{
	mlx_hook(e->window->ptr, 17, 0, cleanup_and_exit, e);
	mlx_hook(e->window->ptr, 4, 1L << 2, mouse_press, e);
	mlx_hook(e->window->ptr, 5, 1L << 3, mouse_release, e);
	mlx_hook(e->window->ptr, 6, 1L << 6, mouse_move, e);
	mlx_hook(e->window->ptr, 2, 1L << 0, key_press, e);
	mlx_hook(e->window->ptr, 3, 1L << 1, key_release, e);
	mlx_hook(e->window->ptr, 22, 1L << 17, handle_resize, e);
	mlx_loop_hook(e->window->mlx_ptr, loop_hook, e);
}
