/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 16:07:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/30 19:12:34 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

bool	process_system(t_scene *scene, t_parse_obj obj)
{
	if (obj.type == TYPE_CAMERA)
	{
		scene->camera = obj.data.camera;
		return (true);
	}
	if (obj.type == TYPE_AMBIENT)
	{
		scene->ambient = obj.data.ambient;
		return (true);
	}
	return (false);
}
