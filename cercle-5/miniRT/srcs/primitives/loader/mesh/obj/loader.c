/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 03:53:28 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"

static bool	obj_finalize_mesh_to_scene(t_obj *obj, t_scene *scene, const char *path)
{
	t_mesh	mesh;
	int		mat_idx;

	if (obj->out_v_count == 0)
	{
		obj_free_obj(obj);
		return (false);
	}
	obj_generate_normals(obj);
	obj_init_mesh(&mesh, obj, path);
	mat_idx = obj->current_mat_id;
	mesh.mat_id = mat_idx;
	obj_free_obj(obj);
	return (scene_add_mesh(scene, mesh));
}

static void	init_obj(t_obj *obj)
{
	ft_memset(obj, 0, sizeof(t_obj));
	obj->current_mat_id = -1;
	obj->first_mtl_id = -1;
	obj->bbox = aabb_create_empty();
}

static void	handle_id_to_scene(t_obj *obj, t_parser *p, t_scene *scene, const char *path)
{
	char	id[16];

	if (!obj_read_id(p, id, sizeof(id)))
		return ;
	if (ft_strcmp(id, "v") == 0)
		obj_parse_v(obj, p);
	else if (ft_strcmp(id, "vt") == 0)
		obj_parse_vt(obj, p);
	else if (ft_strcmp(id, "vn") == 0)
		obj_parse_vn(obj, p);
	else if (ft_strcmp(id, "f") == 0)
		obj_parse_f(obj, p);
	else if (ft_strcmp(id, "mtllib") == 0)
		obj_parse_mtllib_to_scene(obj, p, scene, path);
	else if (ft_strcmp(id, "usemtl") == 0)
		obj_parse_usemtl_to_scene(obj, p, scene);
}

bool	obj_parse_to_asset(t_obj *obj, const char *path)
{
	t_parser	p;
	int			fd;

	init_obj(obj);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (false);
	parser_init(&p, fd);
	while (true)
	{
		parser_skip_spaces(&p);
		if (p.eof && p.cursor >= p.bytes_read)
			break ;
		if (parser_peek(&p) == '#')
		{
			obj_skip_line(&p);
			continue ;
		}
		handle_id_to_scene(obj, &p, NULL, path);
		obj_skip_line(&p);
	}
	close(fd);
	return (true);
}

bool	obj_load(t_scene *scene, const char *path)
{
	t_obj	obj;

	if (!obj_parse_to_asset(&obj, path))
		return (false);
	return (obj_finalize_mesh_to_scene(&obj, scene, path));
}
