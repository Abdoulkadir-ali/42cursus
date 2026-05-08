/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 05:16:50 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/29 07:25:44 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gameplay.h"
#include "engine.h"

void	rotate_player(t_actor *actor, float angle)
{
	float	c;
	float	s;
	t_vec2	n;
	float	mag;

	c = cosf(angle);
	s = sinf(angle);
	n.x = actor->dir.x * c - actor->dir.y * s;
	n.y = actor->dir.x * s + actor->dir.y * c;
	mag = sqrtf(n.x * n.x + n.y * n.y);
	actor->dir.x = n.x / mag;
	actor->dir.y = n.y / mag;
}

static bool	can_move_x(t_world *world, t_vec3 p, float dx, float mx)
{
	if (is_wall(world, (t_vec3){p.x + dx + mx, p.y + MOVE_MARGIN, 0}) == 0
		&& is_wall(world, (t_vec3){p.x + dx + mx, p.y - MOVE_MARGIN, 0}) == 0)
		return (true);
	return (false);
}

static bool	can_move_y(t_world *world, t_vec3 p, float dy, float my)
{
	if (is_wall(world, (t_vec3){p.x + MOVE_MARGIN, p.y + dy + my, 0}) == 0
		&& is_wall(world, (t_vec3){p.x - MOVE_MARGIN, p.y + dy + my, 0}) == 0)
		return (true);
	return (false);
}

static t_vec2	swept_clamp(t_world *world, t_vec3 origin, t_vec2 delta)
{
	t_dda	d;
	t_vec2	ray;
	t_vec3	hit_pt;
	float	want;
	float	hit;

	want = sqrtf(delta.x * delta.x + delta.y * delta.y);
	if (want < 0.00001f)
		return ((t_vec2){0.0f, 0.0f});
	ray.x = delta.x / want;
	ray.y = delta.y / want;
	init_dda(&d, origin, ray);
	run_dda(&d, world->map);
	hit_pt.x = d.hit_pos.x;
	hit_pt.y = d.hit_pos.y;
	hit_pt.z = 0.0f;
	if (!is_wall(world, hit_pt))
		return (delta);
	hit = d.perp_dist - MOVE_MARGIN;
	if (hit <= 0.0f)
		return ((t_vec2){0.0f, 0.0f});
	if (hit >= want)
		return (delta);
	return ((t_vec2){ray.x * hit, ray.y * hit});
}

void	apply_movement(t_world *world, t_vec2 delta)
{
	t_vec2	m;
	t_vec2	cl;

	cl = swept_clamp(world, world->player.actor.pos, delta);
	m.x = -MOVE_MARGIN;
	if (cl.x > 0.0f)
		m.x = MOVE_MARGIN;
	m.y = -MOVE_MARGIN;
	if (cl.y > 0.0f)
		m.y = MOVE_MARGIN;
	if (can_move_x(world, world->player.actor.pos, cl.x, m.x))
		world->player.actor.pos.x += cl.x;
	if (can_move_y(world, world->player.actor.pos, cl.y, m.y))
		world->player.actor.pos.y += cl.y;
}
