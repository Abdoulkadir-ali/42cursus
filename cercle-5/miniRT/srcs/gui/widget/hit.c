/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 03:01:19 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "widget.h"

bool	hit_titlebar(t_widget *w, t_vec2i m)
{
	return (w->draggable
		&& m.x >= w->pos.x
		&& m.x < w->pos.x + w->size.x
		&& m.y >= w->pos.y
		&& m.y < w->pos.y + WIDGET_TITLE_H);
}

bool	hit_body(t_widget *w, t_vec2i m)
{
	size_t	top;

	top = w->pos.y;
	if (w->draggable)
		top += WIDGET_TITLE_H;
	return (m.x >= w->pos.x
		&& m.x < w->pos.x + w->size.x
		&& m.y >= top
		&& m.y < w->pos.y + w->size.y);
}

static bool	hit_msgbox_btn(t_gui *gui, t_widget *w, t_vec2i m, t_vec3i p)
{
	size_t	bx;

	p.z = -1;
	while (++p.z < w->btn_count)
	{
		bx = w->pos.x + 8 + p.z * (p.y + 4);
		if (m.x >= (size_t)bx && m.x < (size_t)(bx + p.y - 4)
			&& m.y >= (size_t)p.x && m.y < (size_t)(p.x + 22))
		{
			if (w->btn_callbacks[p.z])
				w->btn_callbacks[p.z](w, gui);
			return (true);
		}
	}
	return (false);
}

bool	handle_msgbox_click(t_gui *gui, t_widget *w, t_vec2i m)
{
	t_vec3i	p;
	int		div;

	if (!w->visible)
		return (false);
	div = w->btn_count;
	if (div <= 0)
		div = 1;
	p.x = w->pos.y + w->size.y - 28;
	p.y = (w->size.x - 16) / div;
	if (hit_msgbox_btn(gui, w, m, p))
		return (true);
	return (m.x >= w->pos.x
		&& m.x < w->pos.x + w->size.x
		&& m.y >= w->pos.y + 24
		&& m.y < w->pos.y + w->size.y);
}
