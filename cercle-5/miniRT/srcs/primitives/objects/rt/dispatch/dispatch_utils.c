/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 18:21:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/09 19:29:25 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dispatcher.h"

t_parse_obj	dispatch_basic(t_parser *p, char *id)
{
	if (id[0] == 'A' && id[1] == '\0')
		return (parse_ambient(p));
	if (id[0] == 'C' && id[1] == '\0')
		return (parse_camera(p));
	if (id[0] == 'L' && id[1] == '\0')
		return (parse_light(p));
	if (id[0] == 'G' && id[1] == '\0')
		return (parse_big_g(p));
	if (ft_strcmp(id, "grav") == 0)
		return (parse_scene_gravity(p));
	if (ft_strcmp(id, "damp") == 0)
		return (parse_scene_damp(p));
	return (init_none());
}

t_parse_obj	dispatch_shapes(t_parser *p, char *id)
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
	if (id[0] == 'b' && id[1] == 'h')
		return (parse_attractor(p));
	return (init_none());
}

t_parse_obj	dispatch_meshes(t_parser *p, char *id)
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

static t_parse_obj	dispatch_properties(t_parser *p, char *id)
{
	if (ft_strcmp(id, "rough") == 0)
		return (parse_prop_mod(p, MAT_MOD_ROUGHNESS));
	if (ft_strcmp(id, "metal") == 0)
		return (parse_prop_mod(p, MAT_MOD_METALLIC));
	if (ft_strcmp(id, "emit") == 0)
		return (parse_prop_mod(p, MAT_MOD_EMISSION));
	if (ft_strcmp(id, "opac") == 0)
		return (parse_prop_mod(p, MAT_MOD_OPACITY));
	if (ft_strcmp(id, "refl") == 0)
		return (parse_prop_mod(p, MAT_MOD_REFLECTIVITY));
	if (ft_strcmp(id, "ior") == 0)
		return (parse_prop_mod(p, MAT_MOD_IOR));
	if (ft_strcmp(id, "shine") == 0)
		return (parse_prop_mod(p, MAT_MOD_SHININESS));
	if (ft_strcmp(id, "uv_scale") == 0)
		return (parse_prop_mod(p, MAT_MOD_UV_SCALE));
	if (ft_strcmp(id, "emit_power") == 0)
		return (parse_prop_mod(p, MAT_MOD_EMIT_POWER));
	return (init_none());
}

t_parse_obj	dispatch_modifiers(t_parser *p, char *id)
{
	t_parse_obj	obj;

	if (id[0] == 'm' && id[1] == 'a' && id[2] == 't' && id[3] == '\0')
		return (parse_mat_mod(p));
	if (ft_strcmp(id, "bump") == 0)
		return (parse_bump_mod(p));
	if (ft_strcmp(id, "name") == 0)
		return (parse_name_mod(p));
	if (ft_strcmp(id, "phys") == 0)
		return (parse_phys_mod(p));
	obj = dispatch_properties(p, id);
	return (obj);
}
