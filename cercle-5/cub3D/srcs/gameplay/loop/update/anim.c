/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 09:31:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/29 09:31:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gameplay.h"

void	tick_anim(t_world *world, bool shot, bool reload, int el)
{
	float	scale;
	bool	mv;

	mv = (world->player.controller.input.move_forward
			|| world->player.controller.input.move_backward
			|| world->player.controller.input.strafe_left
			|| world->player.controller.input.strafe_right);
	scale = 1.0f;
	if (mv)
	{
		scale = world->player.actor.speed / 2.0f;
		if (world->player.controller.input.sprint)
			scale *= 2.0f;
		if (world->player.controller.input.crouch)
			scale *= 0.5f;
	}
	tick_weapon_anim(&world->weapon_anim, (t_anim_params){
		.fire = shot, .reload = reload, .move = mv,
		.sprint = world->player.controller.input.sprint != 0,
		.move_scale = scale, .attack_scale = 1.5f}, el);
}
