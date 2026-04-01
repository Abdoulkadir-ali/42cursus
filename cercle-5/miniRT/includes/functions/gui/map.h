/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 20:02:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/01 17:21:10 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUI_FUNCTIONS_MAP_H
# define GUI_FUNCTIONS_MAP_H

# include <pthread.h>
# include "gui.h"

/* Prototypes */
void	gui_map_switcher_init(struct s_gui *gui);
void	gui_next_map(struct s_gui *gui);
void	gui_prev_map(struct s_gui *gui);
bool	map_load_entry(struct s_gui *gui, t_map_entry *entry);
void	map_load_async(struct s_gui *gui, t_map_entry *entry);
void	reset_camera_view(struct s_gui *gui);
void	map_manager_destroy(struct s_gui *gui);
void	map_next_press(struct s_gui *gui);
void	map_prev_press(struct s_gui *gui);
void	fill_map_list(struct s_gui *gui);
void	set_current_entry(struct s_gui *gui);

#endif
