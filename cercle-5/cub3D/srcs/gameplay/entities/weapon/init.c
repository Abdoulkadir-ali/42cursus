/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 22:58:30 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/08 02:18:54 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static void	load_all_clips(t_anim *wa, t_window *win, t_world *world)
{
	wa->clips.idle = anim_get_cached_clip(world, win, wa->paths.idle, NULL);
	wa->clips.walking = anim_get_cached_clip(world, win, wa->paths.walking,
			NULL);
	wa->clips.sprint = anim_get_cached_clip(world, win, wa->paths.sprint, NULL);
	wa->clips.shooting = anim_get_cached_clip(world, win, wa->paths.shooting,
			NULL);
	wa->clips.reload = anim_get_cached_clip(world, win, wa->paths.reload, NULL);
}

void	anim_init(t_anim *wa, t_window *win, t_world *world)
{
	t_anim_paths	p;

	if (!wa || !win || !world)
		return ;
	p = wa->paths;
	ft_bzero(wa, sizeof(t_anim));
	wa->paths = p;
	wa->state.playing = 0;
	wa->active_clip = NULL;
	load_all_clips(wa, win, world);
	anim_set_active_clip(wa, wa->clips.idle, 8, 1);
	wa->weapon_type = WEAPON_NONE;
}

void	init_pistol(t_anim *wa, t_window *win, t_world *world)
{
	if (!wa)
		return ;
	wa->paths.idle = "assets/weapons/gun/idle/idle.anim";
	wa->paths.walking = "assets/weapons/gun/walk/walk.anim";
	wa->paths.sprint = "assets/weapons/gun/sprint/sprint.anim";
	wa->paths.shooting = "assets/weapons/gun/shoot/shoot.anim";
	wa->paths.reload = "assets/weapons/gun/reload/reload.anim";
	anim_init(wa, win, world);
	wa->weapon_type = WEAPON_PISTOL;
}
