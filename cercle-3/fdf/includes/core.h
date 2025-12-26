/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 16:20:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/26 15:11:09 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_H
# define CORE_H

# include <X11/Xlib.h>
# include <X11/keysym.h>
# include <mlx.h>
# include <stdlib.h>
# include <sys/time.h>

// MODULE IMPORTS
# include "define.h"
# include "events.h"
# include "graphics.h"
# include "gui.h"
# include "primitives.h"

typedef struct s_data
{
	void				*mlx_ptr;
	void				*win_ptr;
	t_window			*window;
	t_graphics			*graphics;
	t_maps				map_manager;
	t_gui				*gui;
	t_camera_manager	*camera_manager;
}						t_data;

void					init_defaults(t_data *data);
int						init_window_main_image(t_window *window, void *mlx_ptr);
t_window				*init_window(void *mlx_ptr);
int						init_and_render(t_data *data);
int						cleanup_and_exit(t_events *events);
int						main(int argc, char **argv);

#endif