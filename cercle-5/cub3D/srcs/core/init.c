/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 04:34:36 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/07 01:10:03 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void	init_app(t_app *app, t_window *window, t_world *world, char *map_file)
{
	init_window(window);
	app->window = window;
	app->world = world;
	init_gameplay(world, window, map_file, app);
	init_optimization(world);
	world->player.health = 100;
	world->player.armor = 100;
	setup_gameplay_hooks(app);
}
