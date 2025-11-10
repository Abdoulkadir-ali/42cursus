/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:21:26 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/10 18:21:28 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	zoom_in(t_data *data)
{
	double	factor;

	factor = 1.0 + (0.1 * data->camera.zoom_speed);
	data->camera.target_scale *= factor;
	if (data->camera.target_scale > 100)
		data->camera.target_scale = 100;
}

void	zoom_out(t_data *data)
{
	double	factor;

	factor = 1.0 - (0.1 * data->camera.zoom_speed);
	data->camera.target_scale *= factor;
}

void	update_zoom(t_data *data)
{
	double	diff;

	if (data->camera.scale != data->camera.target_scale)
	{
		diff = data->camera.target_scale - data->camera.scale;
		data->camera.scale += diff * 0.15;
		if (fabs(diff) < 0.1)
			data->camera.scale = data->camera.target_scale;
	}
}
