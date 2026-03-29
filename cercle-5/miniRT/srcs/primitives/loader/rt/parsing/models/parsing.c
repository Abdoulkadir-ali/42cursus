/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 07:44:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/29 13:51:13 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static bool	parse_model_config(t_parser *p, char *path, t_vec3 v[4], double *s)
{
	if (!parser_get_next_word(p, path, 1024)) return (false);
	if (!parse_vec3(p, &v[0]) || !parse_vec3(p, &v[1])) return (false);
	*s = parse_double(p);
	if (!parse_vec3(p, &v[2]) || !parse_vec3(p, &v[3])) return (false);
	return (true);
}

static void	apply_overrides(t_mesh_asset *mesh, t_vec3 v[2], double scale, int mat_id)
{
	mesh->transform.pos = vec3_add(mesh->transform.pos, v[0]);
	mesh->transform.rotation.pitch += v[1].x;
	mesh->transform.rotation.yaw += v[1].y;
	mesh->transform.rotation.roll += v[1].z;
	mesh->transform.scale = vec3_scale(mesh->transform.scale, scale);
	if (mat_id >= 0) mesh->mat_id = mat_id;
}

bool	parse_mesh_entry(t_scene *scene, t_parser *p)
{
	char	path[1024]; t_vec3 v[4]; double s; t_mesh_asset m;
	if (!parse_model_config(p, path, v, &s)) return (false);
	if (!mesh_load_from_file(&m, path)) return (false);
	apply_overrides(&m, v, s, scene_add_material_from_color(scene, v[2]));
	return (scene_add_mesh(scene, m));
}

bool	parse_glb_entry(t_scene *scene, t_parser *p)
{
	t_glb glb; char path[1024]; t_vec3 v[4]; double s; int i;
	if (!parse_model_config(p, path, v, &s)) return (false);
	int fd = open(path, O_RDONLY);
	if (fd < 0 || !glb_parse_to_asset(&glb, fd, path)) return (false);
	close(fd);
	i = -1;
	while (++i < glb.mesh_count)
	{
		apply_overrides(&glb.meshes[i], v, s, -1);
		scene_add_mesh(scene, glb.meshes[i]);
		ft_memset(&glb.meshes[i], 0, sizeof(t_mesh_asset));
	}
	glb_clear_asset(&glb);
	return (true);
}

bool	parse_obj_entry(t_scene *scene, t_parser *p)
{
	t_obj obj; char path[1024]; 
	t_vec3 v[4]; 
	double s;
	t_mesh_asset m;
	
	if (!parse_model_config(p, path, v, &s))
		return (false);
	if (!obj_parse_to_asset(&obj, path))
		return (false);
	obj_init_mesh(&m, &obj);
	apply_overrides(&m, v, s, -1);
	scene_add_mesh(scene, m);
	obj_free_obj(&obj);
	return (true);
}

bool	parse_fbx_entry(t_scene *scene, t_parser *p)
{
	t_fbx fbx; char path[1024]; t_vec3 v[4]; double s; int i;
	if (!parse_model_config(p, path, v, &s)) return (false);
	if (!fbx_load_to_asset(&fbx, path)) return (false);
	i = -1;
	while (++i < fbx.mesh_count)
	{
		apply_overrides(&fbx.meshes[i], v, s, -1);
		scene_add_mesh(scene, fbx.meshes[i]);
	}
	fbx_clear_asset(&fbx);
	return (true);
}

bool	parse_fdf_entry(t_scene *scene, t_parser *p)
{
	t_fdf fdf; char path[1024]; t_vec3 v[4]; double s;
	if (!parse_model_config(p, path, v, &s)) return (false);
	if (!fdf_load_to_asset(&fdf, path)) return (false);
	apply_overrides(&fdf.mesh, v, s, -1);
	scene_add_mesh(scene, fdf.mesh);
	return (true);
}

bool	dispatch_meshes(t_scene *scene, t_parser *p, char *id)
{
	if (ft_strcmp(id, "obj") == 0) return (parse_obj_entry(scene, p));
	if (ft_strcmp(id, "glb") == 0) return (parse_glb_entry(scene, p));
	if (ft_strcmp(id, "fbx") == 0) return (parse_fbx_entry(scene, p));
	if (ft_strcmp(id, "fdf") == 0) return (parse_fdf_entry(scene, p));
	if (ft_strcmp(id, "mesh") == 0) return (parse_mesh_entry(scene, p));
	return (false);
}
