/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_window.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 20:01:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/08 17:40:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUI_WINDOW_H
# define GUI_WINDOW_H

# include "t_physics.h"
# include "t_maths.h"

# define PANEL_RADIUS 6

struct s_gui;
struct s_camera_controller;

typedef struct s_window
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	uint32_t	*render_pixels;
	int			bpp;
	int			line_len;
	int			endian;
	t_vec2s		size;
	void		*disp_imgs[3];
	char		*disp_addrs[3];
	int			disp_bpp;
	int			disp_line_len;
	int			disp_endian;
	t_vec2s		disp_size;
	void		*gui_bg_img;
	char		*gui_bg_addr;
	int			gui_bg_line_len;
	int			gui_bg_bpp;
	int			gui_bg_endian;
}	t_window;

typedef struct s_panel
{
	t_vec2i		pos;
	t_vec2s		size;
	int			bg;
	int			brd;
	const char	*lbl;
}	t_panel;

#endif
