/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   performance.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 14:27:44 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/13 16:50:49 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

static void	display_point_stats(t_layout *l, t_gui *gui, char *buffer)
{
	size_t	total;
	size_t	active;
	int		level;

	total = (size_t)gui->map->width * (size_t)gui->map->height;
	level = gui->render_config->detail_level;
	
	/* Calculate Active Points based on Level */
	if (level > 0)
	{
		double multiplier = pow(4.0, (double)level);
		active = (size_t)(total * multiplier);
	}
	else
	{
		float lod = gui->render_config->lod_value;
		if (lod < 1.0f) lod = 1.0f;
		active = (size_t)(total / (lod * lod)); 
	}

	format_number((long long)total, buffer);
	gui_layout_key_value(l, "Raw map points:", buffer);
	format_number((long long)active, buffer);
	gui_layout_key_value(l, "Active points:", buffer);
}



static void	display_scale_options(t_layout *l, t_gui *gui, char *buffer)
{
	format_float(gui->camera->z_scale, buffer);
	gui_layout_key_value(l, "Z-Scale (Z):", buffer);
}

static void	display_toggle_options(t_layout *l, t_gui *gui, char *buffer)
{
	if (gui->camera->use_z_divisor)
		gui_layout_key_value(l, "Z-Divisor (X):", "ON");
	else
		gui_layout_key_value(l, "Z-Divisor (X):", "OFF");
	if (gui->camera->invert_movement)
		gui_layout_key_value(l, "Invert Move (I):", "Camera");
	else
		gui_layout_key_value(l, "Invert Move (I):", "Object");
	if (gui->render_config->use_horizon_culling)
		gui_layout_key_value(l, "Ray Cast (J):", "ON");
	else
		gui_layout_key_value(l, "Ray Cast (J):", "OFF");

	// Add LOD info here if Manual
	if (!gui->render_config->use_adaptive_logic)
	{
		if (gui->render_config->lod_value > 1.01f)
			format_float(gui->render_config->lod_value, buffer);
		else
			ft_strcpy(buffer, "1.0");
		gui_layout_key_value(l, "Manual LOD (Hm/End):", buffer);
	}
}

static void	display_algorithm_info(t_layout *l, t_gui *gui, char *buffer)
{
	if (gui->render_config->render_mode == RENDER_LINES)
		gui_layout_key_value(l, "Algorithm (K):", "Lines");
	else
		gui_layout_key_value(l, "Algorithm (K):", "Triangles");

	if (gui->render_config->filled)
		gui_layout_key_value(l, "Filled (G):", "Yes");
	else
		gui_layout_key_value(l, "Filled (G):", "No");

	(void)buffer;
	if (gui->render_config->render_mode != RENDER_LINES)
	{
		// Tri Count display removed as requested
	}
}

static void	display_tesselation_info(t_layout *l, t_gui *gui, char *buffer)
{
	int		level;
	char	*type_str;

	level = gui->render_config->detail_level;
	if (level > 0)
	{
		type_str = " (TESS)";
		buffer[0] = '+';
		format_number(level, buffer + 1);
	}
	else 
	{
		if (level < 0) type_str = " (LOD)";
		else type_str = " (BASE)";
		format_number(level, buffer);
	}
	
	ft_strlcat(buffer, type_str, 50);
	gui_layout_key_value(l, "Detail Level:", buffer);

	if (gui->render_config->use_adaptive_logic)
		gui_layout_key_value(l, "Mode (M):", "AUTO");
	else
		gui_layout_key_value(l, "Mode (M):", "MANUAL");

	format_number((long long)gui->render_config->target_tesselation_points, buffer);
	gui_layout_key_value(l, "Target Pts (B+/-):", buffer);
}

void	draw_performance_display_layout(t_layout *l, t_gui *gui)
{
	char	buffer[50];

	gui_layout_title(l, "OPTIMIZATIONS");
	display_point_stats(l, gui, buffer);
	display_scale_options(l, gui, buffer);
	display_toggle_options(l, gui, buffer);
	display_algorithm_info(l, gui, buffer);
	display_tesselation_info(l, gui, buffer);
}
