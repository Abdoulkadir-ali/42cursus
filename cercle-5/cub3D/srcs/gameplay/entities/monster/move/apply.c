/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 23:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/27 22:41:42 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "gameplay.h"

static bool	check_x(t_world *world, t_vec2 pos, float dx, float mx)
{
	if (is_wall(world, (t_vec3){pos.x + dx + mx, pos.y + MOVE_MARGIN, 0}))
		return (false);
	if (is_wall(world, (t_vec3){pos.x + dx + mx, pos.y - MOVE_MARGIN, 0}))
		return (false);
	return (true);
}

static bool	check_y(t_world *world, t_vec2 pos, float dy, float my)
{
	if (is_wall(world, (t_vec3){pos.x + MOVE_MARGIN, pos.y + dy + my, 0}))
		return (false);
	if (is_wall(world, (t_vec3){pos.x - MOVE_MARGIN, pos.y + dy + my, 0}))
		return (false);
	return (true);
}

static bool	can_move_axis(t_world *world, t_vec2 pos, float dx, float dy)
{
	float	mx;
	float	my;

	mx = -MOVE_MARGIN;
	if (dx > 0.0f)
		mx = MOVE_MARGIN;
	my = -MOVE_MARGIN;
	if (dy > 0.0f)
		my = MOVE_MARGIN;
	if (dx != 0.0f && !check_x(world, pos, dx, mx))
		return (false);
	if (dy != 0.0f && !check_y(world, pos, dy, my))
		return (false);
	return (true);
}

static t_vec2	get_dir(t_vec2 from, t_vec2 to)
{
	t_vec2	dir;
	float	dist;

	dir = (t_vec2){to.x - from.x, to.y - from.y};
	dist = sqrtf(dir.x * dir.x + dir.y * dir.y);
	if (dist <= 0.05f)
		return ((t_vec2){0, 0});
	dir.x /= dist;
	dir.y /= dist;
	return (dir);
}

void	apply_move(t_world *world, t_entity *ent, t_vec2 t, float s)
{
	t_vec2	dir;
	float	dt;

	dt = world->frame_time_ms / 1000.0f;
	dir = get_dir(ent->pos, t);
	if (dir.x != 0.0f || dir.y != 0.0f)
	{
		if (can_move_axis(world, ent->pos, dir.x * s * dt, 0.0f))
			ent->pos.x += dir.x * s * dt;
		if (can_move_axis(world, ent->pos, 0.0f, dir.y * s * dt))
			ent->pos.y += dir.y * s * dt;
	}
	ent->anim_speed_scale = 1.0f;
	if (ent->state == ENTITY_STATE_WALK || ent->state == ENTITY_STATE_SPRINT)
		ent->anim_speed_scale = s / 1.5f;
}
