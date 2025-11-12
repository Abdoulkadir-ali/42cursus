/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 19:41:24 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/12 17:22:41 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTROLS_H
# define CONTROLS_H

# include "vectors.h"

# define MOUSE_LEFT 1
# define MOUSE_MIDDLE 2
# define MOUSE_RIGHT 3
# define MOUSE_SCROLL_UP 4
# define MOUSE_SCROLL_DOWN 5

# define KEY_UP_ARROW XK_Up
# define KEY_DOWN_ARROW XK_Down
# define KEY_LEFT_ARROW XK_Left
# define KEY_RIGHT_ARROW XK_Right
# define KEY_CTRL_LEFT XK_Control_L
# define KEY_CTRL_RIGHT XK_Control_R
# define KEY_SHIFT_LEFT XK_Shift_L
# define KEY_SHIFT_RIGHT XK_Shift_R
# define KEY_L XK_l
# define KEY_Z XK_z
# define KEY_F XK_f
# define KEY_H XK_h
# define KEY_D XK_d
# define KEY_T XK_t
# define KEY_S XK_s
# define KEY_A XK_a
# define KEY_X XK_x
# define KEY_I XK_i
# define KEY_V XK_v
# define KEY_G XK_g
# define KEY_PLUS XK_plus
# define KEY_MINUS XK_minus
# define KEY_ZERO XK_0
# define KEY_ESC XK_Escape
# define KEY_R XK_r
# define KEY_P XK_p
# define KEY_N XK_n

typedef struct s_mouse
{
	int					left_pressed;
	int					right_pressed;
	int					middle_pressed;
	int					last_x;
	int					last_y;
	int					middle_start_x;
	int					middle_start_y;
}						t_mouse;

typedef struct s_keys
{
	int					up;
	int					down;
	int					left;
	int					right;
	int					ctrl_left;
	int					ctrl_right;
	int					shift_left;
	int					shift_right;
	int					l;
	int					z;
	int					f;
	int					h;
	int					d;
	int					t;
	int					s;
	int					a;
	int					x;
	int					i;
	int					v;
	int					g;
}						t_keys;

#endif
