/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 05:16:50 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/05 23:33:09 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gameplay.h"
#include "engine.h"

void	render_gameplay(t_window *window, t_world *world)
{
	if (window->addr == NULL)
		return ;
	render_raycast_scene(window, world);
	render_minimap(window, world);
	render_debug_shapes(window, world);
	render_crosshair(window, world);
	render_weapon_sprite(window, &world->weapon_anim);
	render_hud(window, world);
	render_window(window);
	render_fps_counter(window, world);
}
