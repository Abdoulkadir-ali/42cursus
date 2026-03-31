/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 20:29:45 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/31 09:48:43 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUI_H
# define GUI_H

/* 1. EXTERNAL DEPENDENCIES */
# include <semaphore.h>
# include <pthread.h>


typedef struct s_gui				t_gui;

/* 2. FORWARD DECLARATIONS */

/* 3. MODULAR HEADERS */
# include "scene.h"
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

void	camera_rotate_yaw(struct s_gui *gui, double delta_yaw);
void	camera_rotate_pitch(struct s_gui *gui, double delta_pitch);
void	get_forward(double pitch, double yaw, t_vec3 *out);
void	apply_movement(struct s_camera_controller *ctrl, t_vec3 fwd, t_vec3 right);
void	smooth_rotation(struct s_gui *gui, struct s_camera_controller *ctrl);
void	smooth_position(struct s_gui *gui, struct s_camera_controller *ctrl);
void	update_fov(struct s_gui *gui, struct s_camera_controller *ctrl);

void	move_forward_press(struct s_gui *gui);
void	move_forward_release(struct s_gui *gui);
void	move_backward_press(struct s_gui *gui);
void	move_backward_release(struct s_gui *gui);
void	move_left_press(struct s_gui *gui);
void	move_left_release(struct s_gui *gui);
void	move_right_press(struct s_gui *gui);
void	move_right_release(struct s_gui *gui);
void	move_up_press(struct s_gui *gui);
void	move_up_release(struct s_gui *gui);
void	move_down_press(struct s_gui *gui);
void	move_down_release(struct s_gui *gui);
void	zoom_in_press(struct s_gui *gui);
void	zoom_in_release(struct s_gui *gui);
void	zoom_out_press(struct s_gui *gui);
void	zoom_out_release(struct s_gui *gui);
void	speed_up_press(struct s_gui *gui);
void	speed_down_press(struct s_gui *gui);
void	clamp_fov(double *fov);

#endif
