/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layout.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 14:27:34 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 01:48:26 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

/**
 * @brief Initialize a layout cursor for panel composition.
 * @param l Layout object to initialize.
 * @param gui GUI object that will receive the rendered text.
 */
void	gui_layout_init(t_layout *l, t_gui *gui)
{
	l->gui = gui;
	l->cursor_y = GUI_PADDING;
	l->padding = 5;
	l->panel_width = GUI_PANEL_WIDTH;
	l->x_start = GUI_PADDING;
}

/**
 * @brief Advance the layout cursor vertically.
 * @param l Layout object to update.
 * @param size Spacer size in pixels.
 */
void	gui_layout_add_spacer(t_layout *l, int size)
{
	l->cursor_y += size;
}

/**
 * @brief Draw a section title and advance the cursor.
 * @param l Layout object controlling the cursor.
 * @param text Title text to display.
 */
void	gui_layout_title(t_layout *l, char *text)
{
	put_colored(l->gui, l->x_start, l->cursor_y, (t_colored_text){text,
		GUI_TITLE_COLOR});
	l->cursor_y += GUI_TITLE_HEIGHT;
}

/**
 * @brief Draw a plain label row and advance the cursor.
 * @param l Layout object controlling the cursor.
 * @param text Label text to display.
 */
void	gui_layout_label(t_layout *l, char *text)
{
	put_text(l->gui, l->x_start, l->cursor_y, text);
	l->cursor_y += GUI_LINE_HEIGHT;
}

/**
 * @brief Draw a key/value row and advance the cursor.
 * @param l Layout object controlling the cursor.
 * @param key Left-side label.
 * @param val Right-side value.
 */
void	gui_layout_key_value(t_layout *l, char *key, char *val)
{
	put_key(l->gui, l->x_start + 10, l->cursor_y, key);
	put_value(l->gui, l->x_start + 120, l->cursor_y, val);
	l->cursor_y += GUI_LINE_HEIGHT;
}
