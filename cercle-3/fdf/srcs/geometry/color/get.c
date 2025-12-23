/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 11:11:41 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/23 21:09:21 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry.h"

t_vec3	int_color_to_rgb(unsigned int color)
{
	t_vec3	c;

	c.x = (color >> 16) & 0xFF;
	c.y = (color >> 8) & 0xFF;
	c.z = color & 0xFF;
	return (c);
}
