/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 15:25:32 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/12 17:29:54 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "data.h"

void	put_text(t_data *data, t_vec2 v, char *text)
{
	mlx_string_put(data->mlx_ptr, data->win_ptr, v.x, v.y, GUI_TEXT_COLOR,
		text);
}

void	put_key(t_data *data, t_vec2 v, char *text)
{
	mlx_string_put(data->mlx_ptr, data->win_ptr, v.x, v.y, GUI_KEY_COLOR, text);
}

void	put_colored(t_data *d, t_vec2 v, char *text, int color)
{
	mlx_string_put(d->mlx_ptr, d->win_ptr, v.x, v.y, color, text);
}

void	put_value(t_data *data, t_vec2 v, char *text)
{
	mlx_string_put(data->mlx_ptr, data->win_ptr, v.x, v.y, GUI_VALUE_COLOR,
		text);
}
