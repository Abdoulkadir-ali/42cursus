/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layout.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 14:27:34 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/13 16:44:46 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

void	gui_layout_init(t_layout *l, t_gui *gui)
{
	l->gui = gui;
	l->cursor_y = GUI_PADDING;
	l->padding = 5;
	l->panel_width = GUI_PANEL_WIDTH;
}

void	gui_layout_add_spacer(t_layout *l, int size)
{
	l->cursor_y += size;
}

void	gui_layout_title(t_layout *l, char *text)
{
	put_colored(l->gui, GUI_PADDING, l->cursor_y, (t_colored_text){text,
		GUI_TITLE_COLOR});
	l->cursor_y += GUI_TITLE_HEIGHT;
}

void	gui_layout_label(t_layout *l, char *text)
{
	put_text(l->gui, GUI_PADDING, l->cursor_y, text);
	l->cursor_y += GUI_LINE_HEIGHT;
}

void	gui_layout_key_value(t_layout *l, char *key, char *val)
{
	put_key(l->gui, GUI_PADDING + 10, l->cursor_y, key);
	put_value(l->gui, GUI_PADDING + 120, l->cursor_y, val);
	l->cursor_y += GUI_LINE_HEIGHT;
}
