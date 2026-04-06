/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_gui.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 20:29:45 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 20:38:14 by abdoali          ###   ########.fr       */
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
# include "t_settings.h"
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
	t_widget			*focused_widget;
	t_widget			*dragging_widget;
	bool				physics_enabled;
	double				phys_accumulator;
	double				phys_fixed_dt;
	size_t				phys_max_steps;
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
	t_physic_engine		phys_engine;
	t_anim_engine		anim_engine;
	t_raytracer_engine	rt_engine;
	t_optimizations		opts;
	t_settings_panel	settings;	t_widget			*tex_popup_input;
	bool					tex_popup_open;	int					tex_status;
	char				tex_status_msg[64];
	unsigned char		font[95][8];
}						t_gui;

#endif
