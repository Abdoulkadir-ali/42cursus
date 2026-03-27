/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 20:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 09:16:46 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

static bool	dispatch_basic(t_scene *scene, t_parser *p, char *id)
{
	if (id[0] == 'A' && id[1] == '\0')
		return (parse_ambient(scene, p));
	if (id[0] == 'C' && id[1] == '\0')
		return (parse_camera(scene, p));
	if (id[0] == 'L' && id[1] == '\0')
		return (parse_light(scene, p));
	return (false);
}

static bool	dispatch_shapes(t_scene *scene, t_parser *p, char *id)
{
	if (id[0] == 's' && id[1] == 'p')
		return (parse_sphere(scene, p));
	if (id[0] == 's' && id[1] == 'l')
		return (parse_spot_light(scene, p));
	if (id[0] == 'p' && id[1] == 'l')
		return (parse_plane(scene, p));
	if (id[0] == 'c' && id[1] == 'y')
		return (parse_cylinder(scene, p));
	if (id[0] == 'c' && id[1] == 'n')
		return (parse_cone(scene, p));
	if (id[0] == 't' && id[1] == 'r')
		return (parse_tri_shape(scene, p));
	if (id[0] == 'r' && id[1] == 'c')
		return (parse_rect(scene, p));
	if (id[0] == 'p' && id[1] == 'y')
		return (parse_pyramid(scene, p));
	if (id[0] == 'b' && id[1] == 'x')
		return (parse_box(scene, p));
	if (id[0] == 'c' && id[1] == 'a')
		return (parse_capsule(scene, p));
	return (false);
}

static bool	dispatch_meshes(t_scene *scene, t_parser *p, char *id)
{
	if (ft_strcmp(id, "fbx") == 0)
		return (parse_mesh_entry(scene, p, TYPE_ANIM));
	if (ft_strcmp(id, "fdf") == 0)
		return (parse_mesh_entry(scene, p, TYPE_MESH));
	if (ft_strcmp(id, "obj") == 0)
		return (parse_mesh_entry(scene, p, TYPE_MESH));
	if (ft_strcmp(id, "glb") == 0)
		return (parse_mesh_entry(scene, p, TYPE_MESH));
	if (id[0] == 'm' && id[1] == '\0')
		return (parse_mesh_entry(scene, p, TYPE_MESH));
	return (false);
}

static void	handle_unknown(t_parser *p)
{
	while (parser_peek(p) && parser_peek(p) != '\n')
		parser_advance(p);
}

bool	dispatch_scan(t_scene *scene, t_parser *p, char *id)
{
	if (!id || !*id)
		return (false);
	if (dispatch_basic(scene, p, id))
		return (true);
	if (dispatch_shapes(scene, p, id))
		return (true);
	if (dispatch_meshes(scene, p, id))
		return (true);
	handle_unknown(p);
	return (false);
}
