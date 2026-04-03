/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/12 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "obj.h"

static void	init(t_obj *obj)
{
	ft_memset(obj, 0, sizeof(t_obj));
	obj->current_mat_id = init_index(0, true);
	obj->first_mtl_id = init_index(0, true);
	obj->bbox = aabb_create_empty();
}

static void	handle_id(t_obj *obj, t_parser *p, t_scene *scene,
		const char *path)
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
		obj_parse_mtllib(scene, obj, p, path);
	else if (ft_strcmp(id, "usemtl") == 0)
		obj_parse_usemtl(scene, obj, p);
}

bool	scene_parse_obj(const char *path, t_scene *scene)
{
	t_parser	p;
	t_obj		obj;
	int			fd;

	init(&obj);
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
		handle_id(&obj, &p, scene, path);
		obj_skip_line(&p);
	}
	close(fd);
	return (obj_build_mesh(scene, &obj, path));
}

bool	parse_obj(const char *path, t_scene *scene)
{
	return (scene_parse_obj(path, scene));
}
