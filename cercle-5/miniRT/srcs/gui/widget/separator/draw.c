/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/05 10:45:08 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "widget.h"

void	widget_draw_separator(t_gui *gui, t_widget *w)
{
	t_panel	line;

	line = (t_panel){.pos = w->pos, .size = vec2i(w->size.x, 1),
		.bg = COL_BORDER, .brd = COL_BORDER};
	draw_panel(gui, line);
}
