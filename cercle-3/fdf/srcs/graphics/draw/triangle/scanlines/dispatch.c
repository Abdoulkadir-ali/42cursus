/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 21:20:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 03:06:21 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

/**
 * @brief Public scanline entry point used by the triangle rasterizer.
 * @param g Graphics state providing image and render settings.
 * @param data Prepared scanline descriptor.
 */
void	draw_horizontal_scanline(t_graphics *g, t_scanline_data data)
{
	draw_horizontal_scanline_z(g, data);
}
