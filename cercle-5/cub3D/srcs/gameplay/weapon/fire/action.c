/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 09:31:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/29 09:46:52 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "gameplay.h"

static void	handle_projectile_spawn(t_world *world, t_player *p, t_vec2 ray)
{
	t_vec2	spawn_pos;

	spawn_pos.x = p->render_pos.x;
	spawn_pos.y = p->render_pos.y;
	spawn_projectile(world, spawn_pos, ray);
}

static void	handle_raycast_fire(t_world *world, t_player *p, t_vec2 ray)
{
	t_dda	d;
	t_vec3	impact;

	init_dda(&d, p->render_pos, ray);
	run_dda(&d, world->map);
	while (is_active_door_passable(world, &d, ray))
		run_dda(&d, world->map);
	calculate_impact(world, ray, d.perp_dist, &impact);
	add_debug_sphere(world, impact, 0.05f, (t_dbg_style){(t_vec3){255, 255, 0},
		2000});
	check_entity_damage(world, ray, d.perp_dist);
}

void	fire_weapon(t_world *world)
{
	t_player	*p;
	t_vec2		ray;

	if (!world || !world->map)
		return ;
	p = &world->player;
	ray.x = p->render_dir.x;
	ray.y = p->render_dir.y;
	if (p->weapon_state.type == WEAPON_MELEE)
		check_entity_damage(world, ray, MELEE_RANGE);
	else if (p->weapon_state.type == WEAPON_PROJECTILE)
		handle_projectile_spawn(world, p, ray);
	else
		handle_raycast_fire(world, p, ray);
}
