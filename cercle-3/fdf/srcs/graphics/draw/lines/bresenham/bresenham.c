/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 00:00:00 by antigravity       #+#    #+#             */
/*   Updated: 2025/12/23 19:55:54 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void	bresenham_raycast(t_graphics *g, t_bresenham_params *p, int flags)
{
	if (flags & B_COLOR_SHIFT)
	{
		if (flags & B_USE_Z)
			bresenham_raycast_shift_z(g, p);
		else
			bresenham_raycast_shift_no_z(g, p);
	}
	else
	{
		if (flags & B_USE_Z)
			bresenham_raycast_z(g, p);
		else
			bresenham_raycast_fast(g, p);
	}
}

void	bresenham(t_graphics *g, t_bresenham_params *p, int flags)
{
	if (flags & B_COLOR_SHIFT)
	{
		if (flags & B_USE_Z)
			bresenham_shift_z(g, p);
		else
			bresenham_shift_no_z(g, p);
	}
	else
	{
		if (flags & B_USE_Z)
			bresenham_z(g, p);
		else
			bresenham_fast(g, p);
	}
}
