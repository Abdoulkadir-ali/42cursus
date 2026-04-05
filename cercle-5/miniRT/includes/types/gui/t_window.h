/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_window.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 20:01:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/05 19:41:29 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUI_WINDOW_H
# define GUI_WINDOW_H

# include "t_physics.h"
# include "t_maths.h"
# include <pthread.h>
# define PANEL_RADIUS 6
# define COL_BG 0x0A0A12
# define COL_ACCENT 0xE0A820
# define COL_FPS 0x20E060
# define COL_TEXT 0xD0D0D8
# define COL_HOVER 0x20C8D0
# define COL_BORDER 0x333340

struct s_gui;
struct s_camera_controller;

typedef struct s_window
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	uint32_t	*render_pixels;
	int		bpp;
	int		line_len;
	int		endian;
	t_vec2i	size;
	void	*disp_imgs[2];
	char	*disp_addrs[2];
	int		disp_bpp;
	int		disp_line_len;
	int		disp_endian;
	t_vec2i	disp_size;
	void	*gui_bg_img;
	char	*gui_bg_addr;
	int		gui_bg_line_len;
	int		gui_bg_bpp;
	int		gui_bg_endian;
	pthread_mutex_t	disp_mutex;
}	t_window;

typedef struct s_panel
{
	t_vec2i		pos;
	t_vec2i		size;
	int			bg;
	int			brd;
	const char	*lbl;
}	t_panel;

#endif
