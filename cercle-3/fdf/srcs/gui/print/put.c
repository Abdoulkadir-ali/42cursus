/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 15:25:32 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/12 20:33:20 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "core.h"

void	put_text(t_gui *gui, int x, int y, char *text)
{
	mlx_string_put(gui->window->mlx_ptr, gui->window->ptr, x, y, GUI_TEXT_COLOR,
		text);
}

void	put_key(t_gui *gui, int x, int y, char *text)
{
	mlx_string_put(gui->window->mlx_ptr, gui->window->ptr, x, y, GUI_KEY_COLOR, text);
}

void	put_colored(t_gui *gui, int x, int y, char *text, int color)
{
	mlx_string_put(gui->window->mlx_ptr, gui->window->ptr, x, y, color, text);
}

void	put_value(t_gui *gui, int x, int y, char *text)
{
	mlx_string_put(gui->window->mlx_ptr, gui->window->ptr, x, y, GUI_VALUE_COLOR,
		text);
}
