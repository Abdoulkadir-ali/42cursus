/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 10:16:23 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "widget.h"
#include <X11/keysym.h>

static void	input_insert_char(t_widget *w, char c)
{
	int	i;

	if (w->cursor_pos >= WIDGET_INPUT_BUF_SIZE - 2)
		return ;
	i = ft_strlen(w->input_buf);
	while (i >= w->cursor_pos)
	{
		w->input_buf[i + 1] = w->input_buf[i];
		i--;
	}
	w->input_buf[w->cursor_pos] = c;
	w->cursor_pos++;
}

static void	input_delete_back(t_widget *w)
{
	int	i;

	if (w->cursor_pos == 0)
		return ;
	i = w->cursor_pos - 1;
	while (w->input_buf[i])
	{
		w->input_buf[i] = w->input_buf[i + 1];
		i++;
	}
	w->cursor_pos--;
}

static bool	input_nav_key(t_widget *w, int keycode)
{
	if (keycode == XK_Left)
	{
		if (w->cursor_pos > 0)
			w->cursor_pos--;
		return (true);
	}
	if (keycode == XK_Right)
	{
		if (w->cursor_pos < ft_strlen(w->input_buf))
			w->cursor_pos++;
		return (true);
	}
	if (keycode == XK_Home)
	{
		w->cursor_pos = 0;
		return (true);
	}
	if (keycode == XK_End)
	{
		w->cursor_pos = ft_strlen(w->input_buf);
		return (true);
	}
	return (false);
}

static void	input_edit_key(t_gui *gui, t_widget *w, int keycode)
{
	int	i;

	if (keycode == XK_Escape)
	{
		w->focused = false;
		gui->focused_widget = NULL;
	}
	else if (keycode == XK_Return || keycode == XK_KP_Enter)
	{
		if (w->on_change)
			w->on_change(w, gui);
	}
	else if (keycode == XK_BackSpace)
		input_delete_back(w);
	else if (keycode == XK_Delete && w->input_buf[w->cursor_pos])
	{
		i = w->cursor_pos;
		while (w->input_buf[i])
		{
			w->input_buf[i] = w->input_buf[i + 1];
			i++;
		}
	}
	else if (keycode >= 32 && keycode <= 126)
		input_insert_char(w, (char)keycode);
}

void	widget_handle_key(struct s_gui *gui, int keycode)
{
	t_widget	*w;

	w = gui->focused_widget;
	if (!w || w->type != WIDGET_INPUT_BOX)
		return ;
	if (!input_nav_key(w, keycode))
		input_edit_key(gui, w, keycode);
}
