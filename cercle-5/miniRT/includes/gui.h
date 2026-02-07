/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 00:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUI_H
# define GUI_H

# include "mlx.h"
# include "maths.h"
# include "raytracing.h"
# include <X11/X.h>
# include <X11/keysym.h>


# define ZOOM_SPEED 2.0
# define MOUSE_SENSITIVITY 0.005

typedef struct s_gui
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			width;
	int			height;
	t_scene		*scene;
	t_bvh		*bvh;
	t_camera	*camera; // Updated from t_object *
	
	// Camera Control State
	double		yaw;
	double		pitch;
	double		target_yaw;
	double		target_pitch;
	t_vec3		target_position;
	double		target_fov;
	double		move_speed;
	double		lerp_factor;
	bool		dirty; // Frame needs update

	// Input State
	int			move_forward_count;
	bool		moving_forward;
	int			move_backward_count;
	bool		moving_backward;
	int			move_left_count;
	bool		moving_left;
	int			move_right_count;
	bool		moving_right;
	int			move_up_count;
	bool		moving_up;
	int			move_down_count;
	bool		moving_down;
	
	int			zoom_in_count;
	bool		zooming_in;
	int			zoom_out_count;
	bool		zooming_out;

	bool		mouse_left_pressed;
	bool		mouse_middle_pressed;
	int			last_mouse_x;
	int			last_mouse_y;

	void		*widgets;
}				t_gui;


typedef struct s_gui	t_gui; // Forward declaration

t_gui	*gui_init(t_scene *scene, t_bvh *bvh);
void	gui_loop(t_gui *gui);
void	gui_render(t_gui *gui);
void	gui_destroy(t_gui *gui);
void	widget_list_draw(void *widgets, t_gui *gui);

// Input Callbacks
int		key_press(int keycode, t_gui *gui);
int		key_release(int keycode, t_gui *gui);
int		mouse_click(int button, int x, int y, t_gui *gui);
int		mouse_release(int button, int x, int y, t_gui *gui);
int		mouse_motion(int x, int y, t_gui *gui);



#endif
