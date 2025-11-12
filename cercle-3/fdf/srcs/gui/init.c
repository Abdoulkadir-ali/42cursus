/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 15:40:28 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/12 15:40:34 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

int	init_gui(t_data *data)
{
	data->gui_img = mlx_new_image(data->mlx_ptr, GUI_PANEL_WIDTH,
			data->win_height);
	if (!data->gui_img)
		return (0);
	data->gui_addr = mlx_get_data_addr(data->gui_img, &data->gui_bpp,
			&data->gui_line_len, &data->gui_endian);
	if (!data->gui_addr)
		return (0);
	return (1);
}