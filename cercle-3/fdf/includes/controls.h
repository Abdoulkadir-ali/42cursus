/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 19:41:24 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/10 22:34:51 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTROLS_H
# define CONTROLS_H

# include "vectors.h"

typedef enum e_projection_type	t_projection_type;

typedef struct s_rotation
{
	double	x;
	double	y;
	double	z;
}	t_rotation;

typedef struct s_color_shift
{
	int	red;
	int	blue;
	int	green;
}	t_color_shift;

typedef struct s_camera
{
	t_rotation			rotation;
	t_vec2d				offset;
	t_vec3d				grid_center;
	t_color_shift		color_shift;
	t_projection_type	projection;
	int					gui_style;
	double				scale;
	double				target_scale;
	double				move_speed;
	double				zoom_speed;
	int					dampening_threshold;
	double				pending_rot_x;
	double				pending_rot_y;
	double				z_scale;
	int					frustum_margin;
	int					spline_segments;
	int					use_z_divisor;
	int					invert_movement;
}	t_camera;

typedef struct s_mouse
{
	int	left_pressed;
	int	right_pressed;
	int	middle_pressed;
	int	last_x;
	int	last_y;
	int	middle_start_x;
	int	middle_start_y;
}	t_mouse;

typedef struct s_keys
{
	int	up;
	int	down;
	int	left;
	int	right;
	int	ctrl_left;
	int	ctrl_right;
	int	shift_left;
	int	shift_right;
	int	l;
	int	z;
	int	f;
	int	h;
	int	d;
	int	t;
	int	s;
	int	a;
	int	x;
	int	i;
	int	v;
}	t_keys;

typedef struct s_keyboard
{
	int	up_arrow;
	int	down_arrow;
	int	left_arrow;
	int	right_arrow;
	int	ctrl_left;
	int	ctrl_right;
	int	shift_left;
	int	shift_right;
	int	p;
	int	n;
	int	s;
	int	esc;
	int	r;
	int	l;
	int	z;
	int	f;
	int	h;
	int	d;
	int	t;
	int	a;
	int	x;
	int	i;
	int	v;
	int	plus;
	int	minus;
	int	zero;
}	t_keyboard;

typedef struct s_mouse_buttons
{
	int	left;
	int	right;
	int	middle;
	int	scroll_up;
	int	scroll_down;
}	t_mouse_buttons;

typedef struct s_buttons
{
	t_keyboard		keyboard;
	t_mouse_buttons	mouse;
}	t_buttons;

typedef struct s_data	t_data;

t_buttons	init_buttons(void);

void		zoom_in(t_data *data);
void		zoom_out(t_data *data);
void		update_zoom(t_data *data);

void		adjust_camera_to_map(t_data *data);

#endif
