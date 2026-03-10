/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 11:11:41 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 03:36:44 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry.h"

/**
 * @brief Convert a packed integer color into an RGB vector.
 * @param color Packed `0xRRGGBB` color value.
 * @return RGB vector containing the unpacked channels.
 */
t_vec3	int_color_to_rgb(unsigned int color)
{
	t_vec3	c;

	c.x = (color >> 16) & 0xFF;
	c.y = (color >> 8) & 0xFF;
	c.z = color & 0xFF;
	return (c);
}
