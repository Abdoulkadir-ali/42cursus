/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 02:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/30 19:33:45 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


static double	fixed_dt_val(t_gui *gui)
{
	if (gui->phys_fixed_dt > 0.0)
		return (gui->phys_fixed_dt);
	return (1.0 / 60.0);
}

#include "gui.h"
#include "physics.h"

void	update_animations(t_gui *gui, double delta)
{
	int		i;
	t_mesh	*mesh;

	if (!gui->scene || gui->scene->clip_count <= 0)
		return ;
	i = 0;
	while (i < gui->scene->mesh_count)
	{
		mesh = &gui->scene->meshes[i];
		if (mesh->skeleton)
		{
			glb_update_mesh_anim(mesh, gui->scene, delta);
			gui->render.dirty = true;
		}
		i++;
	}
}

void	update_physics_step(t_gui *gui, double delta)
{
	double	fixed_dt;
	int		steps;

	if (!gui->scene || !gui->physics_enabled)
		return ;
	fixed_dt = fixed_dt_val(gui);
	if (delta > fixed_dt * 3.0)
		delta = fixed_dt * 3.0;
	gui->phys_accumulator += delta;
	steps = 0;
	while (gui->phys_accumulator >= fixed_dt && steps < 3)
	{
		update_physics(gui->scene, fixed_dt);
		gui->phys_accumulator -= fixed_dt;
		steps++;
	}
	if (steps > 0)
		gui->render.dirty = true;
}

void	update_autorefresh(t_gui *gui)
{
	if (!gui->physics_enabled)
		return ;
	gui->render.dirty = true;
	if (gui->render.scale < GUI_AUTOREFRESH_SCALE)
		gui->render.scale = GUI_AUTOREFRESH_SCALE;
}

void	update_ambient(t_gui *gui)
{
	t_ambient	*amb;

	if (!gui->scene)
		return ;
	amb = &gui->scene->ambient;
	amb->rgb.x = ((gui->ambient_color >> 16) & 0xFF) / 255.0 * gui->ambient_intensity;
	amb->rgb.y = ((gui->ambient_color >> 8) & 0xFF) / 255.0 * gui->ambient_intensity;
	amb->rgb.z = (gui->ambient_color & 0xFF) / 255.0 * gui->ambient_intensity;
	amb->brightness = gui->ambient_intensity;
}
