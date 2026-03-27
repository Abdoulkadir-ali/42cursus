/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 16:21:35 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

static bool	scene_add_ambient(t_scene *scene, t_ambient *new)
{
	scene->ambient.brightness = new.brightness;
	scene->ambient.rgb = new.rgb;
	return (true);
}

bool	parse_ambient(t_scene *scene, t_parser *p)
{
	t_ambient	ambient;

	ft_memset(&ambient, 0, sizeof(t_ambient));
	if (!parse_double_checked(p, &ambient.brightness))
		return (false);
	if (!parse_vec3(p, &ambient.rgb))
		return (false);
	return (scene_add_ambient(scene, &ambient));
}
