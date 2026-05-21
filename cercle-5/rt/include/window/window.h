/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 18:35:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 05:10:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H
# define WINDOW_H

# include <mlx.h>
# include <X11/Xlib.h>
# include <X11/Xutil.h>
# include "input.h"
# include "ui.h"

struct s_app;

# define WIN_W 2560
# define WIN_H 1440
# define MIN_WIN_W 640
# define MIN_WIN_H 360

typedef struct s_win_list
{
	Window	window;
}			t_win_list;

typedef struct s_xvar
{
	Display	*display;
}			t_xvar;

int		window_init(struct s_app *app);
int		window_resize(struct s_app *app, int new_w, int new_h);
void	window_loop(struct s_app *app);
int		on_keydown(int key, struct s_app *app);
int		on_keyup(int key, struct s_app *app);
int		on_mousedown(int btn, int x, int y, struct s_app *app);
int		on_mouseup(int btn, int x, int y, struct s_app *app);
int		on_mousemove(int x, int y, struct s_app *app);
int		on_close(struct s_app *app);
int		on_loop(struct s_app *app);
void	poll_window_size(struct s_app *app);

#endif
