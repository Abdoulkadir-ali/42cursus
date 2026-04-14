/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_unpack.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 03:22:30 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/09 03:22:30 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"

/**
 * @brief Unpacks a packed RGB integer into a [0.0, 255.0] RGB vector.
 */
t_vec3	unpack_rgb(uint32_t c)
{
	t_vec3	v;

	v.x = (double)((c >> 16) & 0xFF);
	v.y = (double)((c >> 8) & 0xFF);
	v.z = (double)(c & 0xFF);
	v.w = 0;
	return (v);
}

/**
 * @brief Unpacks a packed RGB integer into a t_vec3i directly.
 */
t_vec3i	unpack_rgb_v(uint32_t c)
{
	t_vec3i	v;

	v.x = (int)((c >> 16) & 0xFF);
	v.y = (int)((c >> 8) & 0xFF);
	v.z = (int)(c & 0xFF);
	v.w = 1;
	return (v);
}
