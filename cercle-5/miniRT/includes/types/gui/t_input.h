/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_input.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 20:01:30 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/01 13:39:13 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUI_INPUT_H
# define GUI_INPUT_H

# include "t_physics.h"

struct s_gui;

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

#endif
