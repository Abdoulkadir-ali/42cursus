/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layout_engine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 13:32:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/22 14:24:53 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

/* Initialize the layout context at the top of the panel */
void	gui_layout_init(t_layout *l, t_gui *gui)
{
	l->gui = gui;
	l->cursor_y = GUI_PADDING;
	l->padding = 5;
	l->panel_width = GUI_PANEL_WIDTH;
}

/* Add vertical empty space */
void	gui_layout_add_spacer(t_layout *l, int size)
{
	l->cursor_y += size;
}

/* Draw a colored section title and advance cursor */
void	gui_layout_title(t_layout *l, char *text)
{
	put_colored(l->gui, GUI_PADDING, l->cursor_y,
		(t_colored_text){text, GUI_TITLE_COLOR});
	l->cursor_y += GUI_TITLE_HEIGHT;
}

/* Draw a simple text label */
void	gui_layout_label(t_layout *l, char *text)
{
	put_text(l->gui, GUI_PADDING, l->cursor_y, text);
	l->cursor_y += GUI_LINE_HEIGHT;
}

/* Draw a Key-Value pair (e.g. "FPS: 60") */
void	gui_layout_key_value(t_layout *l, char *key, char *val)
{
	/* Draw Key (Left aligned) */
	put_key(l->gui, GUI_PADDING + 10, l->cursor_y, key);

	/* Draw Value (Right column aligned) */
	/* 120px is the fixed offset column for values */
	put_value(l->gui, GUI_PADDING + 120, l->cursor_y, val);

	l->cursor_y += GUI_LINE_HEIGHT;
}