/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 15:25:32 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 01:51:31 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

/**
 * @brief Draw standard GUI text in the primary text color.
 * @param gui GUI object providing the MLX window handles.
 * @param x Text x position.
 * @param y Text y position.
 * @param text String to draw.
 */
void	put_text(t_gui *gui, int x, int y, char *text)
{
	mlx_string_put(gui->window->mlx_ptr, gui->window->ptr, x, y,
		GUI_TEXT_COLOR, text);
}

/**
 * @brief Draw a key label in the GUI key color.
 * @param gui GUI object providing the MLX window handles.
 * @param x Text x position.
 * @param y Text y position.
 * @param text Key label to draw.
 */
void	put_key(t_gui *gui, int x, int y, char *text)
{
	mlx_string_put(gui->window->mlx_ptr, gui->window->ptr, x, y,
		GUI_KEY_COLOR, text);
}

/**
 * @brief Draw text using an explicit color payload.
 * @param gui GUI object providing the MLX window handles.
 * @param x Text x position.
 * @param y Text y position.
 * @param text Colored text descriptor containing the string and color.
 */
void	put_colored(t_gui *gui, int x, int y, t_colored_text text)
{
	mlx_string_put(gui->window->mlx_ptr, gui->window->ptr, x, y, text.color,
		text.text);
}

/**
 * @brief Draw a value string in the GUI value color.
 * @param gui GUI object providing the MLX window handles.
 * @param x Text x position.
 * @param y Text y position.
 * @param text Value string to draw.
 */
void	put_value(t_gui *gui, int x, int y, char *text)
{
	mlx_string_put(gui->window->mlx_ptr, gui->window->ptr, x, y,
		GUI_VALUE_COLOR, text);
}
