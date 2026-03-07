/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entry_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 20:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/12 20:50:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

bool	rt_parse_mesh_position(t_parser *p, t_parse_obj *obj)
{
	return (parse_vec3(p, &obj->data.mesh_info.transform.pos));
}

bool	rt_parse_mesh_rotation(t_parser *p, t_parse_obj *obj)
{
	t_vec3	rot;

	if (!parse_vec3(p, &rot))
		return (false);
	obj->data.mesh_info.transform.rotation = (t_rotator){rot.x, rot.y, rot.z};
	return (true);
}

void	rt_parse_mesh_color(t_parser *p, t_parse_obj *obj)
{
	parser_skip_spaces(p);
	if (parser_peek(p) && parser_peek(p) != '\n')
		parse_vec3(p, &obj->data.mesh_info.color);
}

void	rt_parse_mesh_emission(t_parser *p, t_parse_obj *obj)
{
	parser_skip_spaces(p);
	if (parser_peek(p) && parser_peek(p) != '\n')
		parse_vec3(p, &obj->data.mesh_info.emission);
}

t_parse_obj	rt_mesh_fail(t_parse_obj obj)
{
	free(obj.data.mesh_info.path);
	obj.type = TYPE_NONE;
	return (obj);
}
