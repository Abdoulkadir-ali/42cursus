/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/13 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

t_vec3	clamp_color(t_vec3 color)
{
	if (color.x > 1.0 || color.y > 1.0 || color.z > 1.0)
		DBG_WARN_MSG(DBG_CH_RENDER,
			"clamp_color: overflow r=%.2f g=%.2f b=%.2f\n",
			color.x, color.y, color.z);
	color.x = fmin(fmax(color.x, COLOR_MIN), COLOR_MAX);
	color.y = fmin(fmax(color.y, COLOR_MIN), COLOR_MAX);
	color.z = fmin(fmax(color.z, COLOR_MIN), COLOR_MAX);
	return (color);
}

t_vec3	pixel_color(t_vec3 obj, t_vec3 light, double intensity)
{
	t_vec3	f;

	f.x = obj.x * light.x * intensity / COLOR_MAX;
	f.y = obj.y * light.y * intensity / COLOR_MAX;
	f.z = obj.z * light.z * intensity / COLOR_MAX;
	return (f);
}
