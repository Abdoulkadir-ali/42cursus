/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   soft_body.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/12 02:10:03 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

/*
** Parses a soft-body line from the .rt file.
**
** Syntax:
**   sb <mesh_path> [stiffness] [damping]
**
** Example:
**   sb maps/obj/human/human.obj 400.0 8.0
**
** stiffness defaults to 200.0 (N/m) if omitted.
** damping   defaults to  5.0  (N·s/m) if omitted.
**
** The mesh_info.sb_stiffness / sb_damping fields carry these values forward
** so inject_one() can call scene_build_soft_body() after the mesh is loaded.
*/

static void	init_sb_defaults(t_mesh_info *info)
{
	ft_memset(&info->transform, 0, sizeof(t_transform));
	info->transform.forward = vec3(0, 0, 1);
	info->transform.up = vec3(0, 1, 0);
	info->transform.right = vec3(1, 0, 0);
	info->transform.scale = vec3(1, 1, 1);
	info->color = vec3(255, 255, 255);
	info->sb_stiffness = 200.0;
	info->sb_damping = 5.0;
}

static bool	parse_sb_path(t_parser *p, t_mesh_info *info)
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
		return (false);
	info->path = ft_strdup(path);
	return (info->path != NULL);
}

t_parse_obj	parse_soft_body(t_parser *p)
{
	t_parse_obj	res;

	ft_memset(&res, 0, sizeof(res));
	res.type = TYPE_NONE;
	if (!parse_sb_path(p, &res.data.mesh_info))
		return (res);
	init_sb_defaults(&res.data.mesh_info);
	parser_skip_spaces(p);
	if (parser_peek(p) && parser_peek(p) != '\n')
		res.data.mesh_info.sb_stiffness = parse_double(p);
	parser_skip_spaces(p);
	if (parser_peek(p) && parser_peek(p) != '\n')
		res.data.mesh_info.sb_damping = parse_double(p);
	parser_skip_spaces(p);
	if (parser_peek(p) && parser_peek(p) != '\n')
		parse_vec3(p, &res.data.mesh_info.transform.pos);
	res.type = TYPE_SOFT_BODY;
	return (res);
}
