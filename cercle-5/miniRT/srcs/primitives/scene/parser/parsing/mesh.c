/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/05 22:56:46 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

static char	*parse_mesh_path(t_parser *p)
{
	char	path[512];
	int		i;

	parser_skip_spaces(p);
	i = 0;
	while (i < 511 && parser_peek(p) && !ft_isspace(parser_peek(p)))
	{
		path[i++] = parser_peek(p);
		parser_advance(p);
	}
	path[i] = '\0';
	if (i == 0)
		return (NULL);
	return (ft_strdup(path));
}

static void	init_mesh_transform(t_mesh_info *info)
{
	ft_memset(&info->transform, 0, sizeof(t_transform));
	info->transform.forward = vec3(0, 0, 1);
	info->transform.up = vec3(0, 1, 0);
	info->transform.right = vec3(1, 0, 0);
	info->transform.scale = vec3(1, 1, 1);
	info->color = vec3(255, 255, 255);
	info->emission = vec3(0, 0, 0);
}

/**
 * Parses a mesh entry from the buffered parser.
 * Format: <path> <pos_x,pos_y,pos_z> <rot_x,rot_y,rot_z> <scale> <r,g,b> [emissive_r,emissive_g,emissive_b]
 */
t_parse_obj	parse_mesh_entry(t_parser *p, t_type type)
{
	t_parse_obj	res;
	t_vec3		rot;
	double		scale;
	char		nc;

	ft_memset(&res, 0, sizeof(res));
	res.type = TYPE_NONE;
	res.data.mesh_info.path = parse_mesh_path(p);
	if (!res.data.mesh_info.path)
		return (res);
	init_mesh_transform(&res.data.mesh_info);
	parser_skip_spaces(p);
	if (!parser_peek(p) || parser_peek(p) == '\n')
	{
		res.type = type;
		return (res);
	}
	parse_vec3(p, &res.data.mesh_info.transform.pos);
	parser_skip_spaces(p);
	if (!parser_peek(p) || parser_peek(p) == '\n')
	{
		res.type = type;
		return (res);
	}
	parse_vec3(p, &rot);
	res.data.mesh_info.transform.rotation.pitch = rot.x;
	res.data.mesh_info.transform.rotation.yaw = rot.y;
	res.data.mesh_info.transform.rotation.roll = rot.z;
	parser_skip_spaces(p);
	nc = parser_peek(p);
	if (!nc || nc == '\n')
	{
		res.type = type;
		return (res);
	}
	scale = parse_double(p);
	if (scale > 0.0)
		res.data.mesh_info.transform.scale = vec3(scale, scale, scale);
	parser_skip_spaces(p);
	nc = parser_peek(p);
	if (!nc || nc == '\n')
	{
		res.type = type;
		return (res);
	}
	parse_vec3(p, &res.data.mesh_info.color);
	parser_skip_spaces(p);
	nc = parser_peek(p);
	if (nc && nc != '\n')
		parse_vec3(p, &res.data.mesh_info.emission);
	res.type = type;
	return (res);
}
