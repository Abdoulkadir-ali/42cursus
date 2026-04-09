/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_v.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 17:42:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/08 17:42:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "color.h"

t_vec3i	rt_unpack_color_v(size_t c)
{
	return (unpack_rgb_v((uint32_t)c));
}

size_t	rt_pack_color_v(t_vec3i v)
{
	return ((size_t)pack_rgb_v(v));
}
