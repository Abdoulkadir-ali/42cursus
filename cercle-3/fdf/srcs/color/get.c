/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 11:11:41 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/13 11:18:36 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"

unsigned char	get_red(unsigned int color)
{
	return ((color >> 16) & 0xFF);
}

unsigned char	get_green(unsigned int color)
{
	return ((color >> 8) & 0xFF);
}

unsigned char	get_blue(unsigned int color)
{
	return (color & 0xFF);
}

t_vec3	get_color_vec3(unsigned int color)
{
	return ((t_vec3){(int)get_red(color), (int)get_green(color),
			(int)get_blue(color)});
}
