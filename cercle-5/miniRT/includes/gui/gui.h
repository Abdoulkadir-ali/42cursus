/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 20:29:45 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/30 22:17:08 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUI_H
# define GUI_H

/* 1. EXTERNAL DEPENDENCIES */
# include <semaphore.h>
# include <pthread.h>
# include "core.h"
# include "physics.h"
# include "debug.h"
# include "maths.h"
# include "raytracing.h"
# include "scene.h"
# include "editor.h"

typedef struct s_gui				t_gui;

/* 2. FORWARD DECLARATIONS */

/* 3. MODULAR HEADERS */
# include "widget.h"
# include "window.h"
# include "render.h"
# include "camera.h"
# include "input.h"
# include "map.h"
# include "editor.h"

/* 4. MAIN AGGREGATOR STRUCTURE */

struct s_gui
{
	t_window			win;
	t_scene				*scene;
	struct s_camera_controller	cam_ctrl;
	t_render_state		render;
	t_input				input;
	struct s_map		map_info;
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
};

#endif
