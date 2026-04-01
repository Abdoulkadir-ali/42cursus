/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_camera.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 09:24:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/01 13:39:06 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_GUI_CAMERA_H
# define TYPES_GUI_CAMERA_H

# include "t_maths.h"

typedef struct s_camera_controller
{
	t_camera	*camera;
	t_transform	transform;
	t_vec3		target_pos;
	t_rotator	target_rot;
	double		target_fov;
	double		move_speed;
	double		lerp_factor;
	bool		moving_forward;
	bool		moving_backward;
	bool		moving_left;
	bool		moving_right;
	bool		moving_up;
	bool		moving_down;
	bool		zooming_in;
	bool		zooming_out;
	bool		mouse_left_pressed;
	bool		mouse_middle_pressed;
	t_vec2i		last_mouse;
}				t_camera_controller;
#endif
