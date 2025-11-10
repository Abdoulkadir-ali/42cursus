/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 19:41:39 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/10 22:36:24 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUI_H
# define GUI_H


typedef struct s_data	t_data;

/* ========== GUI CONSTANTS ========== */
# define GUI_PANEL_WIDTH 280
# define GUI_PADDING 15
# define GUI_LINE_HEIGHT 18
# define GUI_TITLE_HEIGHT 25

// Colors
# define GUI_BG_COLOR 0x1A1A1A
# define GUI_BORDER_COLOR 0x404040
# define GUI_TEXT_COLOR 0xE0E0E0
# define GUI_TITLE_COLOR 0x00D4FF
# define GUI_VALUE_COLOR 0x00FF88
# define GUI_KEY_COLOR 0xFFAA00

/* ========== GUI FUNCTIONS ========== */
int		init_gui(t_data *data);
void	render_gui(t_data *data);
void	draw_panel_background(t_data *data);
void	draw_controls_guide_at(t_data *data, int *y);
void	draw_speed_display_at(t_data *data, int *y);
void	draw_projection_display_at(t_data *data, int *y);
void	draw_map_name_display_at(t_data *data, int *y);
void	draw_performance_display_at(t_data *data, int *y);

#endif
