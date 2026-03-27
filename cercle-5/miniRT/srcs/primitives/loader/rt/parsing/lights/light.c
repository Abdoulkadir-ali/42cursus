/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 16:19:52 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

static bool	scene_add_light(t_scene *scene, t_light light)
{
	if (!DYNARRAY_ENSURE_INT(&scene->lights, &scene->light_count,
			&scene->light_cap, sizeof(t_light)))
		return (false);
	scene->lights[scene->light_count++] = light;
	return (true);
}

bool	parse_light(t_scene *scene, t_parser *p)
{
	t_light	light;

	ft_memset(&light, 0, sizeof(t_light));
	light.type = LIGHT_POINT;
	if (!parse_vec3(p, &light.transform.pos))
		return (false);
	light.brightness = parse_double(p);
	light.rgb = vec3(255, 255, 255);
	parser_skip_spaces(p);
	if (parser_peek(p) && parser_peek(p) != '\n')
		parse_vec3(p, &light.rgb);
	return (scene_add_light(scene, light));
}

