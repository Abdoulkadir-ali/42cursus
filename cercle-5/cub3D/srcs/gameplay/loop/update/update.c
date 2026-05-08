/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 05:16:50 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/08 04:15:43 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void	handle_movement_input(t_world *world, t_player_input *input,
		float speed, float dt)
{
	t_vec3	dir;

	dir = world->player.actor.dir;
	if (input->move_forward)
		apply_movement(world, (t_vec2){dir.x * speed * dt, dir.y * speed * dt});
	if (input->move_backward)
		apply_movement(world, (t_vec2){-dir.x * speed * dt, -dir.y * speed
			* dt});
	if (input->strafe_left)
		apply_movement(world, (t_vec2){dir.y * speed * dt, -dir.x * speed
			* dt});
	if (input->strafe_right)
		apply_movement(world, (t_vec2){-dir.y * speed * dt, dir.x * speed
			* dt});
}

static void	apply_rotation(t_world *world, t_player_controller *ctrl)
{
	if (ctrl->input.rotate_left)
		rotate_player(&world->player.actor, 0.03f);
	if (ctrl->input.rotate_right)
		rotate_player(&world->player.actor, -0.03f);
	if (ctrl->input.pitch_up)
		world->player.pitch_offset -= 0.03f;
	if (ctrl->input.pitch_down)
		world->player.pitch_offset += 0.03f;
	if (world->player.pitch_offset > 0.5f)
		world->player.pitch_offset = 0.5f;
	if (world->player.pitch_offset < -0.5f)
		world->player.pitch_offset = -0.5f;
}

static void	apply_vertical(t_world *world, t_player_controller *ctrl, float dt)
{
	t_player	*p;

	p = &world->player;
	if (ctrl->input.jump && p->pos_z <= 0.001f && p->vel_z <= 0.001f)
		p->vel_z = JUMP_IMPULSE;
	p->vel_z -= GRAVITY_ACCEL * dt;
	p->pos_z += p->vel_z * dt;
	if (p->pos_z <= 0.0f && !ctrl->input.crouch)
	{
		p->pos_z = 0.0f;
		if (p->vel_z < 0.0f)
			p->vel_z = 0.0f;
	}
	if (ctrl->input.crouch && p->pos_z > MIN_POS_Z)
		p->pos_z -= 1.0f * dt;
	if (p->pos_z > MAX_POS_Z)
	{
		p->pos_z = MAX_POS_Z;
		p->vel_z = 0.0f;
	}
	if (p->pos_z < MIN_POS_Z)
		p->pos_z = MIN_POS_Z;
	p->render_pos_z = p->pos_z;
}

static void	apply_weapon_switch(t_world *world, t_player_controller *ctrl)
{
	if (ctrl->input.switch_weapon == 0)
		return ;
	if (ctrl->input.switch_weapon == 1)
		world->player.weapon_state.type = WEAPON_PISTOL;
	else if (ctrl->input.switch_weapon == 2)
		world->player.weapon_state.type = WEAPON_MELEE;
	else if (ctrl->input.switch_weapon == 3)
		world->player.weapon_state.type = WEAPON_PROJECTILE;
	ctrl->input.switch_weapon = 0;
}

void	apply_action_flags(t_world *world, int elapsed_us)
{
	t_player_controller	*ctrl;
	float				speed;
	float				dt;

	ctrl = &world->player.controller;
	speed = world->player.actor.speed;
	if (ctrl->input.sprint)
		speed *= 2.0f;
	else if (ctrl->input.crouch)
		speed *= 0.5f;
	dt = (float)elapsed_us / 1000000.0f;
	handle_movement_input(world, &ctrl->input, speed, dt);
	apply_rotation(world, ctrl);
	apply_vertical(world, ctrl, dt);
	apply_weapon_switch(world, ctrl);
	if (ctrl->input.interact)
	{
		if (!try_interact_push(world))
			try_interact_door(world);
		ctrl->input.interact = 0;
	}
	tick_push_walls(world, dt);
	sync_push_grid(world);
}
