/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 20:01:30 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 16:03:13 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUI_FUNCTIONS_INPUT_H
# define GUI_FUNCTIONS_INPUT_H


# include <X11/X.h>
# include <X11/keysym.h>
# include "editor.h"
# include "map.h"
# include "camera.h"

/* Prototypes */
int		key_press(int keycode, struct s_gui *gui);
int		key_release(int keycode, struct s_gui *gui);
int		mouse_click(int button, t_vec2i mouse, struct s_gui *gui);
int		mouse_release(int button, struct s_gui *gui);
int		mouse_motion(t_vec2i mouse, struct s_gui *gui);
void	gui_update_input(struct s_gui *gui);
int		(*mouse_click_hook(void))(int b, int x, int y, void *p);
int		(*mouse_release_hook(void))(int b, int x, int y, void *p);
int		(*mouse_motion_hook(void))(int x, int y, void *param);

/* srcs/engines/physics/integrate/interaction.c */
void	physics_shoot_ray(t_scene *scene, t_ray ray, double impulse);

/* Keyboard press/release actions */
void	move_forward_press(t_gui *gui);
void	move_forward_release(t_gui *gui);
void	move_backward_press(t_gui *gui);
void	move_backward_release(t_gui *gui);
void	move_left_press(t_gui *gui);
void	move_left_release(t_gui *gui);
void	move_right_press(t_gui *gui);
void	move_right_release(t_gui *gui);
void	move_up_press(t_gui *gui);
void	move_up_release(t_gui *gui);
void	move_down_press(t_gui *gui);
void	move_down_release(t_gui *gui);
void	zoom_in_press(t_gui *gui);
void	zoom_in_release(t_gui *gui);
void	zoom_out_press(t_gui *gui);
void	zoom_out_release(t_gui *gui);
void	speed_up_press(t_gui *gui);
void	speed_down_press(t_gui *gui);
void	exit_press(t_gui *gui);
void    fullres_toggle(struct s_gui *gui);
void	shoot_force(struct s_gui *gui, t_vec2i mouse);
void	handle_scroll(int b, struct s_gui *gui);

#endif
