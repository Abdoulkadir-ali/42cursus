/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 20:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/31 09:49:19 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUI_CAMERA_H
# define GUI_CAMERA_H

# include "helpers.h"
# include "types.h"

typedef struct s_camera_controller
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
} t_camera_controller;

void	camera_move(t_camera *camera, t_vec3 direction, double speed);
void	camera_move_forward(t_camera *camera, double speed);
void	camera_move_backward(t_camera *camera, double speed);
void	camera_move_left(t_camera *camera, double speed);
void	camera_move_right(t_camera *camera, double speed);
void	camera_move_up(t_camera *camera, double speed);
void	camera_move_down(t_camera *camera, double speed);

#endif
