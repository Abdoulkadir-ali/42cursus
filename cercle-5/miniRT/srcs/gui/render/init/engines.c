/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 00:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	gui_init_physics(t_gui *gui)
{
	gui->physics_enabled = true;
	gui->phys_accumulator = 0.0;
	gui->phys_fixed_dt = 1.0 / 60.0;
	gui->phys_max_steps = 5;
	gui->ambient_color = 0xFFFFFF;
	gui->ambient_intensity = 1.0;
	gui->phys_engine.scene = gui->scene;
	gui->phys_engine.settings.slop = 0.005;
	gui->phys_engine.settings.baumgarte = 0.2;
	gui->phys_engine.settings.solver_iterations = 10;
	gui->phys_engine.settings.restitution_slop = 0.5;
	gui->phys_engine.settings.gravity = vec3(0, -9.81, 0);
	gui->phys_engine.settings.global_damping = 0.999;
	gui->phys_engine.settings.time_scale = 1.0;
	gui->phys_engine.settings.mesh_simplify_collision = 0;
	gui->phys_engine.pool.initialized = 0;
}

void	gui_init_anim(t_gui *gui)
{
	gui->anim_engine.enabled = true;
	gui->anim_engine.time_scale = 1.0;
}

void	gui_init_render(t_gui *gui)
{
	gui->render.dirty = true;
	gui->render.abort_render = false;
	gui->render.back_idx = 0;
	optimizations_init(gui);
	font_load(gui, FONT_PATH);
}
