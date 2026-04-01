/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 20:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/01 17:44:23 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUI_CAMERA_H
# define GUI_CAMERA_H

# include "types.h"

# define ZOOM_SPEED         2.0
# define MOUSE_SENSITIVITY  0.005

void	camera_move(t_camera *camera, t_vec3 direction, double speed);
void	camera_move_forward(t_camera *camera, double speed);
void	camera_move_backward(t_camera *camera, double speed);
void	camera_move_left(t_camera *camera, double speed);
void	camera_move_right(t_camera *camera, double speed);
void	camera_move_up(t_camera *camera, double speed);
void	camera_move_down(t_camera *camera, double speed);

void	camera_rotate_yaw(t_gui *gui, double delta_yaw);
void	camera_rotate_pitch(t_gui *gui, double delta_pitch);
void	get_forward(double pitch, double yaw, t_vec3 *out);
void	apply_movement(t_camera_controller *ctrl, t_vec3 fwd, t_vec3 right);
void	smooth_rotation(t_gui *gui, t_camera_controller *ctrl);
void	smooth_position(t_gui *gui, t_camera_controller *ctrl);
void	update_fov(t_gui *gui, t_camera_controller *ctrl);
void	clamp_fov(double *fov);

#endif
