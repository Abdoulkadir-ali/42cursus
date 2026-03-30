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
	color.x = fmin(fmax(color.x, 0.0), 255.0);
	color.y = fmin(fmax(color.y, 0.0), 255.0);
	color.z = fmin(fmax(color.z, 0.0), 255.0);
	return (color);
}

t_vec3	pixel_color(t_vec3 obj, t_vec3 light, double intensity)
{
	t_vec3	f;

	f.x = obj.x * light.x * intensity / 255.0;
	f.y = obj.y * light.y * intensity / 255.0;
	f.z = obj.z * light.z * intensity / 255.0;
	return (f);
}
