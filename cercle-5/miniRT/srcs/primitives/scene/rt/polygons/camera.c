/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 21:10:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

bool	parse_camera(t_scene *scene, t_parser *p)
{
	t_parse_obj	parsed;

	parsed = rt_parse_camera_obj(p);
	if (parsed.type != TYPE_CAMERA)
		return (false);
	return (scene_add_camera(scene, parsed.data.camera));
}
