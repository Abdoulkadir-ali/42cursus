/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 17:35:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/31 09:41:31 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions/primitives/objects/surface.h"

void	apply_magic_colors(t_material *m, t_vec3 color)
{
	if (color.x == 255 && color.y == 0 && color.z == 255)
	{
		m->refract_index = 1.5;
		m->transparency = 0.9;
		m->reflectivity = 0.1;
		m->specular = 0.9;
		m->shininess = 128.0;
	}
	else if (color.x == 0 && color.y == 255 && color.z == 255)
	{
		m->reflectivity = 0.8;
		m->specular = 0.9;
		m->shininess = 256.0;
	}
	else if (color.x == 0 && color.y == 0 && color.z == 255)
	{
		m->refract_index = 1.33;
		m->transparency = 0.8;
		m->reflectivity = 0.2;
		m->specular = 0.8;
		m->shininess = 64.0;
	}
}

void	apply_more_magic_colors(t_material *m, t_vec3 color)
{
	if (color.x == 200 && color.y == 160 && color.z == 255)
	{
		m->refract_index = 1.5;
		m->transparency = 0.7;
		m->reflectivity = 0.2;
		m->specular = 0.9;
		m->shininess = 128.0;
	}
	else if (color.x == 255 && color.y == 255 && color.z == 0)
	{
		m->emission = vec3(255, 255, 150);
		m->albedo_map.color_a = vec3(255, 255, 150);
		m->specular = 0.0;
		m->shininess = 1.0;
	}
}
