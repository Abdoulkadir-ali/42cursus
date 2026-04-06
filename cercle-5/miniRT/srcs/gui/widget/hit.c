/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 10:13:34 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "widget.h"

bool	hit_titlebar(t_widget *w, t_vec2i m)
{
	return (w->draggable && phit(m, w->pos, vec2s(w->size.x, WIDGET_TITLE_H)));
}

bool	hit_body(t_widget *w, t_vec2i m)
{
	int	top;

	top = w->pos.y;
	if (w->draggable)
		top += WIDGET_TITLE_H;
	return (phit(m, vec2i(w->pos.x, top),
			vec2s(w->size.x, w->pos.y + w->size.y - top)));
}

bool	handle_msgbox_click(t_gui *gui, t_widget *w, t_vec2i m)
{
	size_t	btn_w;
	t_vec2i	btn_pos;
	size_t	i;
	size_t	div;

	if (!w->visible)
		return (false);
	div = w->btn_count;
	if (div == 0)
		div = 1;
	btn_w = (w->size.x - 16) / div;
	btn_pos.y = w->pos.y + w->size.y - 28;
	i = 0;
	while (i < w->btn_count)
	{
		btn_pos.x = w->pos.x + 8 + i * (btn_w + 4);
		if (phit(m, btn_pos, vec2s(btn_w - 4, 22)))
		{
			if (w->btn_callbacks[i])
				w->btn_callbacks[i](w, gui);
			return (true);
		}
		i++;
	}
	return (phit(m, vec2i(w->pos.x, w->pos.y + 24),
			vec2s(w->size.x, w->size.y - 24)));
}
