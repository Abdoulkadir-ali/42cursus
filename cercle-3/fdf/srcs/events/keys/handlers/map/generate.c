/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 00:35:00 by antigravity       #+#    #+#             */
/*   Updated: 2025/12/24 03:05:45 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"
#include "generator.h"
#include "graphics.h"

int	handle_g(int keycode, t_events *events)
{
	t_gen_params	params;

	(void)keycode;
	params.width = events->map->width;
	params.height = events->map->height;
	if (params.width < 50)
		params.width = 50;
	if (params.height < 50)
		params.height = 50;
	params.scale = 4.0;
	params.z_scale = 20.0;
	params.octaves = 4;
	params.persistence = 0.5;
	params.seed = time(NULL);
	return (0);
}
