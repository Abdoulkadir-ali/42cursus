/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 01:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/08 04:32:10 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void	render_debug_shapes(t_window *win, t_world *world)
{
	size_t	i;

	i = 0;
	while (i < MAX_DEBUG_SHAPES)
	{
		if (world->debug_shapes[i].active)
		{
			if (world->debug_shapes[i].type == DEBUG_SPHERE)
				draw_debug_sphere(win, world, &world->debug_shapes[i]);
		}
		i++;
	}
}
