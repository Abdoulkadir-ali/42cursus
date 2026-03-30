/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 20:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/30 22:17:08 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUI_CAMERA_H
# define GUI_CAMERA_H

# include "core.h"
# include "physics.h"
# include "maths.h"

typedef struct s_camera_controller	t_camera_controller;

struct s_camera_controller
{
	t_camera *camera;
	t_transform transform;
	t_vec3 target_pos;
	t_rotator target_rot;
	double target_fov;
	double move_speed;
	double lerp_factor;
	bool moving_forward;
	bool moving_backward;
	bool moving_left;
	bool moving_right;
	bool moving_up;
	bool moving_down;
	bool zooming_in;
	bool zooming_out;
	bool mouse_left_pressed;
	bool mouse_middle_pressed;
	t_vec2i last_mouse;
};

void	camera_move(t_camera *camera, t_vec3 direction, double speed);
void	camera_move_forward(t_camera *camera, double speed);
void	camera_move_backward(t_camera *camera, double speed);
void	camera_move_left(t_camera *camera, double speed);
void	camera_move_right(t_camera *camera, double speed);
void	camera_move_up(t_camera *camera, double speed);
void	camera_move_down(t_camera *camera, double speed);
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
