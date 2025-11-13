/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 15:25:32 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/13 11:39:48 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"


void	put_text(t_data *data, int x, int y, char *text)
{
	mlx_string_put(data->mlx_ptr, data->win_ptr, x, y, GUI_TEXT_COLOR,
		text);
}

void	put_key(t_data *data, int x, int y, char *text)
{
	mlx_string_put(data->mlx_ptr, data->win_ptr, x, y, GUI_KEY_COLOR, text);
}

void	put_colored(t_gui *gui, int x, int y, t_colored_text text)
{
	mlx_string_put(gui->window->mlx_ptr, gui->window->ptr, x, y, text.color, text.text);
}

void	put_value(t_data *data, int x, int y, char *text)
{
	mlx_string_put(data->mlx_ptr, data->win_ptr, x, y, GUI_VALUE_COLOR,
		text);
}
