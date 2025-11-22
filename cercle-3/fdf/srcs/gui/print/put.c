/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 15:25:32 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/22 14:29:18 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

void	put_text(t_gui *gui, int x, int y, char *text)
{
	mlx_string_put(gui->window->mlx_ptr, gui->window->ptr, x, y, GUI_TEXT_COLOR,
		text);
}

void	put_key(t_gui *gui, int x, int y, char *text)
{
	mlx_string_put(gui->window->mlx_ptr, gui->window->ptr, x, y, GUI_KEY_COLOR,
		text);
}

void	put_colored(t_gui *gui, int x, int y, t_colored_text colored)
{
	mlx_string_put(gui->window->mlx_ptr, gui->window->ptr, x, y, colored.color,
		colored.text);
}

void	put_value(t_gui *gui, int x, int y, char *text)
{
	mlx_string_put(gui->window->mlx_ptr, gui->window->ptr, x, y,
		GUI_VALUE_COLOR, text);
}
