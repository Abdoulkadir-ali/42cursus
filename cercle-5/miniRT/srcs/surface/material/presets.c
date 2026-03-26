/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   presets.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 04:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 04:50:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "surface.h"

static void	apply_transparent_preset(t_material *m, double ior, double transp,
		double refl)
{
	m->refract_index = ior;
	m->transparency = transp;
	m->reflectivity = refl;
	m->specular = 0.9;
	m->shininess = 128.0;
}

void	material_apply_preset(t_material *m, t_vec3 color)
{
	if (vec3_compare(color, COLOR_MAGENTA) || vec3_compare(color, COLOR_LAVENDER))
		apply_transparent_preset(m, 1.5, 0.8, 0.2);
	else if (vec3_compare(color, COLOR_CYAN))
	{
		m->reflectivity = 0.8;
		m->specular = 0.9;
		m->shininess = 256.0;
	}
	else if (vec3_compare(color, COLOR_BLUE))
		apply_transparent_preset(m, 1.33, 0.8, 0.2);
	else if (vec3_compare(color, COLOR_YELLOW))
	{
		m->emission = (t_vec3){255.0, 255.0, 150.0};
		m->albedo_map.color_a = (t_vec3){255.0, 255.0, 150.0};
		m->specular = 0.0;
		m->shininess = 1.0;
	}
}
