/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 20:01:30 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/31 09:49:52 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUI_INPUT_H
# define GUI_INPUT_H

# include "physics.h"
# include "helpers.h"
# include "types.h"

typedef struct s_input				t_input;

# define BUTTON_LEFT 1
# define BUTTON_MIDDLE 2
# define BUTTON_RIGHT 3
# define BUTTON_SCROLL_UP 4
# define BUTTON_SCROLL_DOWN 5

typedef struct s_input
{
	int				mouse_x;
	int				mouse_y;
}	t_input;

typedef struct s_key_action
{
	int		key;
	void	(*press_action)(struct s_gui *gui);
	void	(*release_action)(struct s_gui *gui);
}	t_key_action;

/* Prototypes */
int		key_press(int keycode, struct s_gui *gui);
int		key_release(int keycode, struct s_gui *gui);
int		mouse_click(int button, t_vec2i mouse, struct s_gui *gui);
int		mouse_release(int button, t_vec2i mouse, struct s_gui *gui);
int		mouse_motion(t_vec2i mouse, struct s_gui *gui);
void	gui_update_input(struct s_gui *gui);

#endif
