/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 20:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/12 20:50:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dispatcher.h"

static t_parse_obj	init_none(void)
{
	t_parse_obj	obj;

	obj.type = TYPE_NONE;
	return (obj);
}

static t_parse_obj	dispatch_basic(t_parser *p, char *id)
{
	if (id[0] == 'A' && id[1] == '\0')
		return (parse_ambient(p));
	if (id[0] == 'C' && id[1] == '\0')
		return (parse_camera(p));
	if (id[0] == 'L' && id[1] == '\0')
		return (parse_light(p));
	return (init_none());
}

static t_parse_obj	dispatch_shapes(t_parser *p, char *id)
{
	if (id[0] == 's' && id[1] == 'p')
		return (parse_sphere(p));
	if (id[0] == 's' && id[1] == 'l')
		return (parse_spot_light(p));
	if (id[0] == 'p' && id[1] == 'l')
		return (parse_plane(p));
	if (id[0] == 'c' && id[1] == 'y')
		return (parse_cylinder(p));
	if (id[0] == 'c' && id[1] == 'n')
		return (parse_cone(p));
	if (id[0] == 't' && id[1] == 'r')
		return (parse_tri_shape(p));
	if (id[0] == 'r' && id[1] == 'c')
		return (parse_rect(p));
	if (id[0] == 'p' && id[1] == 'y')
		return (parse_pyramid(p));
	if (id[0] == 'b' && id[1] == 'x')
		return (parse_box(p));
	if (id[0] == 'c' && id[1] == 'a')
		return (parse_capsule(p));
	return (init_none());
}

static t_parse_obj	dispatch_meshes(t_parser *p, char *id)
{
	if (ft_strcmp(id, "fbx") == 0)
		return (parse_mesh_entry(p, TYPE_ANIM));
	if (ft_strcmp(id, "fdf") == 0)
		return (parse_mesh_entry(p, TYPE_MESH));
	if (ft_strcmp(id, "obj") == 0)
		return (parse_mesh_entry(p, TYPE_MESH));
	if (ft_strcmp(id, "glb") == 0)
		return (parse_mesh_entry(p, TYPE_MESH));
	if (id[0] == 'm' && id[1] == '\0')
		return (parse_mesh_entry(p, TYPE_MESH));
	return (init_none());
}

t_parse_obj	dispatch_scan(t_parser *p, char *id)
{
	t_parse_obj	obj;

	if (!id || !*id)
		return (init_none());
	obj = dispatch_basic(p, id);
	if (obj.type != TYPE_NONE)
		return (obj);
	obj = dispatch_shapes(p, id);
	if (obj.type != TYPE_NONE)
		return (obj);
	return (dispatch_meshes(p, id));
}
