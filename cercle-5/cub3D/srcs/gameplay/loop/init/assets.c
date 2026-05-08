/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 02:31:48 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/08 02:18:49 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gameplay.h"
#include "texture.h"

static void	init_door_animations(t_world *world, t_window *win, t_app *app)
{
	world->door_open_clip = anim_get_cached_clip(world, win,
			"assets/door/open/open.anim", app);
	world->door_close_clip = anim_get_cached_clip(world, win,
			"assets/door/close/close.anim", app);
}

static void	init_monster_animations(t_world *world, t_window *win, t_app *app)
{
	world->monster_idle = anim_get_cached_clip(world, win,
			"assets/monster/idle/idle.anim", app);
	world->monster_walk = anim_get_cached_clip(world, win,
			"assets/monster/walk/walk.anim", app);
	world->monster_sprint = anim_get_cached_clip(world, win,
			"assets/monster/sprint/sprint.anim", app);
	world->monster_attack = anim_get_cached_clip(world, win,
			"assets/monster/attack/attack.anim", app);
	world->monster_die = anim_get_cached_clip(world, win,
			"assets/monster/die/die.anim", app);
}

void	init_gameplay_assets(t_world *world, t_window *window, t_app *app)
{
	load_texture(&world->crosshair, "assets/weapons/crosshair/red.xpm", world,
		app);
	init_door_animations(world, window, app);
	init_monster_animations(world, window, app);
}
