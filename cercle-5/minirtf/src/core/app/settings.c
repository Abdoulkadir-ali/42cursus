/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 01:24:10 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/02 17:30:30 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

static void	settings_defaults_ext(t_app *app)
{
	app->set.render.accum_cap = 256;
	app->set.render.selection_outline = true;
	app->set.render.pick_buffer = true;
	app->set.rt.blackbody = true;
	app->set.rt.collision_heat = false;
	app->set.anim.anim_skinning = true;
	app->set.anim.use_mips = true;
	app->set.anim.mip_bias = 0.0f;
	app->set.rt.soft_shadows = false;
	app->set.rt.shadow_samples = 1;
	app->set.rt.indirect_light = false;
	app->set.render.taa = false;
	app->set.rt.shadow_ray_gate = 50.0f;
	app->set.render.brightness = 0.0f;
	app->set.render.contrast = 1.05f;
	app->set.render.saturation = 1.15f;
	app->set.render.gamma = 2.2f;
	app->set.render.vignette = 0.0f;
}

void	settings_defaults(t_app *app)
{
	app->set.rt.max_bounces = 2;
	app->set.rt.shadows = true;
	app->set.render.downscale = 1;
	app->set.controls.show_gui = true;
	app->set.rt.show_normals = false;
	app->set.physics.physics_on = true;
	app->set.rt.lensing_on = true;
	app->set.rt.emitters_as_lights = true;
	app->set.render.downscale_on_move = true;
	app->set.physics.phys_substeps = 1.0f;
	app->set.controls.move_speed = MOVE_SPEED;
	app->set.controls.mouse_sens = MOUSE_SENS;
	app->set.rt.emit_mult = 1.0f;
	app->set.physics.friction = 0.25f;
	app->set.render.exposure = 1.0f;
	app->set.render.progressive = true;
	settings_defaults_ext(app);
	app->selected = 0x7fffffff;
	app->dirty = 1;
	app->running = 1;
}
