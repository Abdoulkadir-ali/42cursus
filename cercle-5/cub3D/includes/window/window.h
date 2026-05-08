/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 02:45:37 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/26 15:57:29 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H
# define WINDOW_H

/* UTILITIES */
# include "error.h"
# include "exit.h"
# include "libft.h"
# include <stdlib.h>
# include <mlx.h>

/* DEPENDENCIES */
# include "X11/keysym.h"

# define BASE_WIDTH 1280
# define BASE_HEIGHT 720

# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1080

# define COL_BLACK 0x00000000
# define COL_WHITE 0x00FFFFFF
# define COL_RED 0x00FF0000
# define COL_GREEN 0x0000FF00
# define COL_BLUE 0x000000FF
# define COL_TRANSPARENT 0x00000000
# define COL_ALPHA_MASK 0xFF000000

/* MINIMAP COLORS */
# define COL_MM_WALL 0x00DCDCDC
# define COL_MM_DOOR 0x00C89632
# define COL_MM_OPEN_DOOR 0x00966E1E
# define COL_MM_FLOOR 0x003C3C3C
# define COL_MM_PLAYER 0x00FF5000
# define COL_MM_DIR 0x00FFC800

/* RAYCASTING COLORS */
# define COL_RAY_WALL_L 0x00DCDCDC
# define COL_RAY_WALL_D 0x00969696
# define COL_RAY_DOOR_L 0x00B47828
# define COL_RAY_DOOR_D 0x0082551C

typedef struct s_window
{
	int		width;
	int		height;
	char	*title;
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	float	*z_buffer;
	int		mm_cell;
	int		mm_margin;
}			t_window;

void		init_window(t_window *game);
void		handle_window_resize(t_window *win, int new_w, int new_h);
void		render_window(t_window *win);

void		free_window(t_window *win);
void		setup_resize_hook(t_app *app);

#endif
