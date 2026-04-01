/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/01 18:13:09 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

/**
 * Parses a mesh entry from the buffered parser.
 * Format: <path> <pos_x,pos_y,pos_z> <rot_x,rot_y,rot_z> <scale>
 */
t_parse_obj	parse_mesh_entry(t_parser *p, t_type type)
{
	t_parse_obj	res;
	char		path[512];
	int			i;

	ft_memset(&res, 0, sizeof(res));
	res.type = TYPE_NONE;
	parser_skip_spaces(p);
	i = 0;
	while (i < 511 && parser_peek(p) && !ft_isspace(parser_peek(p)))
	{
		path[i++] = parser_peek(p);
		parser_advance(p);
	}
	path[i] = '\0';
	if (i == 0)
		return (res);
	res.data.mesh_info.path = ft_strdup(path);
	if (!res.data.mesh_info.path)
		return (res);
	ft_memset(&res.data.mesh_info.transform, 0, sizeof(t_transform));
	res.data.mesh_info.transform.forward = vec3(0, 0, 1);
	res.data.mesh_info.transform.up = vec3(0, 1, 0);
	res.data.mesh_info.transform.right = vec3(1, 0, 0);
	parser_skip_spaces(p);
	if (parser_peek(p) && parser_peek(p) != '\n')
		parse_vec3(p, &res.data.mesh_info.transform.pos);
	res.data.mesh_info.color = vec3(255, 255, 255);
	res.type = type;
	return (res);
}
