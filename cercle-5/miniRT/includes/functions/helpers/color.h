/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 12:19:12 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# include "types.h"
# include <stdint.h>

/**
 * @brief Packs normalized [0.0, 1.0] OR [0.0, 255.0] RGB vector into a single
 * integer (RGB format).
 * 
 * @param v The RGB vector.
 * @return uint32_t The packed color.
 */
uint32_t	pack_rgb(t_vec3 v);

/**
 * @brief Unpacks a packed RGB integer into a normalized [0.0, 255.0] RGB vector.
 */
t_vec3		unpack_rgb(uint32_t c);

/**
 * @brief Unpacks a packed RGB integer into a t_vec3i directly.
 */
t_vec3i		unpack_rgb_v(uint32_t c);

/**
 * @brief Clips a color vector values to [0.0, 255.0].
 * 
 * @param color The color vector to clip.
 * @return t_vec3 The clipped color vector.
 */
t_vec3		clip_color(t_vec3 color);

/**
 * @brief Converts a color from t_vec3 to t_vec3i (clamping included).
 */
t_vec3i		vec3_to_rgb(t_vec3 v);

/**
 * @brief Packs a t_vec3i into a uint32_t.
 */
uint32_t	pack_rgb_v(t_vec3i v);

#endif
