/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_entry.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 20:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/12 20:50:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

t_parse_obj	parse_mesh_entry(t_parser *p, t_type type)
{
	t_parse_obj	obj;
	char		path[1024];

	obj.type = TYPE_NONE;
	if (!rt_parse_token(p, path, sizeof(path)))
		return (obj);
	obj.type = type;
	obj.data.mesh_info.path = ft_strdup(path);
	obj.data.mesh_info.color = vec3(255, 255, 255);
	if (!rt_parse_mesh_position(p, &obj))
		return (rt_mesh_fail(obj));
	if (!rt_parse_mesh_rotation(p, &obj))
		return (rt_mesh_fail(obj));
	rt_parse_scale(p, &obj);
	rt_parse_mesh_color(p, &obj);
	return (obj);
}
