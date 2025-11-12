/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 15:25:32 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/12 19:59:28 by abdoali          ###   ########.fr       */
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

void	put_colored(t_data *d, int x, int y, char *text, int color)
{
	mlx_string_put(d->mlx_ptr, d->win_ptr, x, y, color, text);
}

void	put_value(t_data *data, int x, int y, char *text)
{
	mlx_string_put(data->mlx_ptr, data->win_ptr, x, y, GUI_VALUE_COLOR,
		text);
}
