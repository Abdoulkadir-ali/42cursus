/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/08 17:09:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "widget.h"

void	widget_draw_separator(t_gui *gui, t_widget *w)
{
	t_panel	line;

	line.pos = w->pos;
	line.size = vec2s(w->size.x, 1);
	line.bg = COL_BORDER;
	line.brd = COL_BORDER;
	line.lbl = NULL;
	draw_panel(gui, line);
}
