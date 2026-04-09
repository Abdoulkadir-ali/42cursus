/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insp_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 12:33:39 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include <X11/keysym.h>

bool	insp_row_click(t_gui *gui, t_vec2i mouse, t_vec2i pos, t_islider sl)
{
	t_vec2s	d;
	int		x_off;
	int		w;
	int		ix;

	d = gui->win.disp_size;
	x_off = pos.x + ui_sx(INSP_SL_OFF, d);
	w = ui_sx(INSP_SL_W, d);
	ix = pos.x + ui_sx(INSP_IN_OFF, d);
	if (mouse.x >= x_off && mouse.x < x_off + w
		&& mouse.y >= pos.y
		&& mouse.y < pos.y + ui_sy(INSP_ROW_STEP, d))
	{
		set_insp_drag(gui, sl, mouse.x, vec2i(x_off, w));
		return (true);
	}
	if (mouse.x >= ix && mouse.x < ix + ui_sx(INSP_IN_W, d)
		&& mouse.y >= pos.y
		&& mouse.y < pos.y + ui_sy(INSP_ROW_STEP, d))
	{
		set_insp_edit(gui, sl);
		return (true);
	}
	return (false);
}

static void	insp_input_char(t_insp_edit *e, int keycode)
{
	int		i;
	int		ci;

	if (ft_strlen(e->buf) >= 30)
		return ;
	ci = e->i;
	i = ft_strlen(e->buf);
	while (i >= ci)
	{
		e->buf[i + 1] = e->buf[i];
		i--;
	}
	e->buf[e->i] = (char)keycode;
	e->i++;
}

static void	insp_input_edit(t_gui *gui, int keycode)
{
	t_insp_edit	*e;
	int			i;

	e = &gui->slider_state.insp_edit;
	if (keycode == XK_BackSpace && e->i > 0)
	{
		i = e->i - 1;
		while (e->buf[i])
		{
			e->buf[i] = e->buf[i + 1];
			i++;
		}
		e->i--;
	}
	else if ((keycode >= '0' && keycode <= '9')
		|| keycode == '.' || keycode == '-'
		|| keycode == 'e' || keycode == 'E')
		insp_input_char(e, keycode);
}

void	insp_input_key(t_gui *gui, int keycode)
{
	t_insp_edit	*e;

	e = &gui->slider_state.insp_edit;
	if (!e->active)
		return ;
	if (keycode == XK_Escape)
	{
		e->active = false;
		e->value_ptr = NULL;
	}
	else if (keycode == XK_Return || keycode == XK_KP_Enter)
		insp_input_commit(gui);
	else if (!insp_input_nav(e, keycode))
		insp_input_edit(gui, keycode);
}
