/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_gui.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 20:29:45 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/01 13:38:52 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_GUI_H
# define TYPES_GUI_H

/* 1. EXTERNAL DEPENDENCIES */
# include <pthread.h>
# include <semaphore.h>

/* 2. MODULAR HEADERS */
# include "t_camera.h"
# include "t_editor.h"
# include "t_input.h"
# include "t_map.h"
# include "t_render.h"
# include "t_scene.h"
# include "t_widget.h"
# include "t_window.h"

/* 3. MAIN AGGREGATOR STRUCTURE */
typedef struct s_gui
{
	t_window			win;
	t_scene				*scene;
	t_camera_controller	cam_ctrl;
	t_render_state		render;
	t_input				input;
	t_map				map_info;
	t_widget			*widgets;
	bool				physics_enabled;
	double				phys_accumulator;
	double				phys_fixed_dt;
	int					phys_max_steps;
	int					ambient_color;
	double				ambient_intensity;
	t_selection			selection;
	t_inspector			inspector;
	t_scene_panel		scene_panel;
	t_slider_state		slider_state;
	t_map_job			map_job;
	t_crud_ui			crud;
	t_hover_cache		hover;
	t_transform			transform;
}						t_gui;

#endif
