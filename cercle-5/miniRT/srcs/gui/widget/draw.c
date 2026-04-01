/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 06:25:55 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/01 13:01:37 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "widget.h"

void	widget_draw_label(t_gui *gui, t_widget *w)
{
	if (w->label)
		mlx_string_put(gui->win.mlx, gui->win.win, w->pos.x, w->pos.y
			+ w->size.y / 2, COL_TEXT, w->label);
	else
		mlx_string_put(gui->win.mlx, gui->win.win, w->pos.x, w->pos.y
			+ w->size.y / 2, COL_TEXT, "");
}

void	widget_draw_checkbox(t_gui *gui, t_widget *w)
{
	char	buf[128];

	if (w->value)
		buf[0] = 'X';
	else
		buf[0] = ' ';
	buf[1] = '\0';
	if (w->label)
		snprintf(buf + 2, sizeof(buf) - 2, "] %s", w->label);
	else
		snprintf(buf + 2, sizeof(buf) - 2, "]");
	mlx_string_put(gui->win.mlx, gui->win.win, w->pos.x, w->pos.y + w->size.y
		/ 2, COL_TEXT, buf);
}

void	widget_draw_all(t_gui *gui)
{
	t_widget	*w;

	w = gui->widgets;
	while (w)
	{
		if (w->type == WIDGET_CHECKBOX)
			widget_draw_checkbox(gui, w);
		else if (w->type == WIDGET_LABEL)
			widget_draw_label(gui, w);
		else if (w->type == WIDGET_SLIDER)
			widget_draw_slider(gui, w);
		w = w->next;
	}
}
