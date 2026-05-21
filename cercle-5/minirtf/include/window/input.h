/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 18:47:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/02 17:17:12 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_Q 113
# define KEY_E 101
# define KEY_Z 122
# define KEY_SPACE 32
# define KEY_LSHIFT 65505
# define KEY_LCTRL 65507
# define KEY_ESC 65307
# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_PLUS 61
# define KEY_MINUS 45

# include <stdbool.h>

typedef struct s_controls_settings
{
	float	move_speed;
	float	mouse_sens;
	bool	show_gui;
}			t_controls_settings;

typedef struct s_input
{
	int	keys[65536];
	int	mouse_x;
	int	mouse_y;
	int	mouse_dx;
	int	mouse_dy;
	int	mouse_wheel;
	int	mouse_left;
	int	mouse_right;
	int	mouse_middle;
	int	mouse_left_clicked;
	int	mouse_right_clicked;
	int	mouse_middle_clicked;
	int	mouse_left_released;
	int	mouse_right_released;
	int	last_mx;
	int	last_my;
	int	first_motion;
	int	lmb_cam_drag;
	int	lmb_press_x;
	int	lmb_press_y;
	int	lmb_drag_dist;
	int	rmb_cam_drag;
	int	rmb_press_x;
	int	rmb_press_y;
	int	rmb_drag_dist;
}		t_input;

static inline int	key_held(t_input *in, int key)
{
	if (key < 0 || key >= 65536)
		return (0);
	return (in->keys[key]);
}

static inline void	key_set(t_input *in, int key, int state)
{
	if (key >= 0 && key < 65536)
		in->keys[key] = state;
}

#endif
