/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:14:05 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/13 11:11:56 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"

int	clamp(int value, int min, int max)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);
	return (value);
}

unsigned int	create_color(unsigned char r, unsigned char g, unsigned char b)
{
	return (((unsigned int)r << 16) | ((unsigned int)g << 8) | (unsigned int)b);
}

unsigned int	create_color_rgb(t_vec3 rgb)
{
	return (create_color((unsigned char)rgb.x, (unsigned char)rgb.y, (unsigned char)rgb.z));
}

unsigned int	create_color_wrap(int r, int g, int b)
{
	return (create_color((unsigned char)r, (unsigned char)g, (unsigned char)b));
}
