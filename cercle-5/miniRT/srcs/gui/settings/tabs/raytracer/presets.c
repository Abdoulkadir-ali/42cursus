/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 00:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "settings.h"

void	apply_preset(t_gui *gui, t_rt_preset p)
{
	t_raytracer_settings	*s;

	s = &gui->rt_engine.settings;
	if (p == RT_PRESET_NATURAL)
	{
		s->brightness = 50.0;
		s->contrast = 52.0;
		s->saturation = 50.0;
		s->gamma = 55.0;
	}
	else if (p == RT_PRESET_VIVID)
	{
		s->brightness = 55.0;
		s->contrast = 65.0;
		s->saturation = 70.0;
		s->gamma = 48.0;
	}
	else if (p == RT_PRESET_CINEMATIC)
	{
		s->brightness = 45.0;
		s->contrast = 60.0;
		s->saturation = 35.0;
		s->gamma = 54.0;
	}
	gui->render.dirty = true;
}

void	on_color_change(t_gui *gui)
{
	gui->rt_engine.settings.preset = RT_PRESET_CUSTOM;
	gui->render.dirty = true;
}
