/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   injection.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 06:40:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 06:32:17 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "debug.h"

void	scene_apply_ambient(t_scene *scene, double brightness, t_vec3 rgb)
{
	scene->ambient.brightness = brightness;
	scene->ambient.rgb = rgb;
}

bool	scene_add_light(t_scene *scene, t_light light)
{
	DBG_INFO_MSG(DBG_CH_PARSER, "inject_lights: count=%zu\n",
		scene->light_count);
	DBG_TRACE_MSG(DBG_CH_PARSER, "inject light[%zu] type=%d\n",
		scene->light_count, (int)light.type);
	if (!DYNARRAY_ENSURE_INT(&scene->lights, &scene->light_count,
			&scene->light_cap, sizeof(t_light)))
		return (false);
	scene->lights[scene->light_count++] = light;
	return (true);
}

bool	scene_add_spot_light(t_scene *scene, t_light light)
{
	light.type = LIGHT_SPOT;
	return (scene_add_light(scene, light));
}
