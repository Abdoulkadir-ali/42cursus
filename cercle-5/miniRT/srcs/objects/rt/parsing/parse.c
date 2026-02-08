/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 19:17:36 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/08 02:25:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "objects/fbx.h"
#include "objects/fdf.h"
#include "objects/obj.h"
#include "objects/rt.h"
#include "scene.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

t_parse_obj	parse_line(char *line)
{
	char		**tokens;
	t_parse_obj	obj;

	obj.type = TYPE_NONE;
	tokens = ft_split(line, ' ');
	if (!tokens || !tokens[0])
	{
		free_split(tokens);
		return (obj);
	}
	if (ft_strcmp(tokens[0], "A") == 0)
		obj = parse_ambient(tokens);
	else if (ft_strcmp(tokens[0], "C") == 0)
		obj = parse_camera(tokens);
	else if (ft_strcmp(tokens[0], "L") == 0)
		obj = parse_light(tokens);
	else if (ft_strcmp(tokens[0], "sp") == 0)
		obj = parse_sphere(tokens);
	else if (ft_strcmp(tokens[0], "pl") == 0)
		obj = parse_plane(tokens);
	else if (ft_strcmp(tokens[0], "cy") == 0)
		obj = parse_cylinder(tokens);
	else if (ft_strcmp(tokens[0], "cn") == 0)
		obj = parse_cone(tokens);
	else if (ft_strcmp(tokens[0], "sl") == 0)
		obj = parse_spot_light(tokens);
	else if (ft_strcmp(tokens[0], "fbx") == 0)
		obj = parse_mesh_entry(tokens, TYPE_ANIM);
	else if (ft_strcmp(tokens[0], "obj") == 0)
		obj = parse_mesh_entry(tokens, TYPE_MESH);
	else if (ft_strcmp(tokens[0], "fdf") == 0)
		obj = parse_mesh_entry(tokens, TYPE_MESH); // FDF also results in a mesh
	free_split(tokens);
	return (obj);
}

static bool	process_line(t_scene *scene, char *line)
{
	t_parse_obj		obj;
	size_t			len;
	bool			ret;
	const char		*ext;
	t_skinned_mesh	*anim;
	t_mesh			*mesh;

	ret = true;
	if (!line || *line == '\0')
		return (true);
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	obj = parse_line(line);
	if (obj.type == TYPE_NONE)
		return (true);
	
	ext = NULL;
	if (obj.type == TYPE_ANIM || obj.type == TYPE_MESH)
		ext = strrchr(obj.data.mesh_info.path, '.');

	// Direct Injection via specialized adders
	if (obj.type == TYPE_SPHERE)
		ret = scene_add_sphere(scene, obj.data.sphere);
	else if (obj.type == TYPE_PLANE)
		ret = scene_add_plane(scene, obj.data.plane);
	else if (obj.type == TYPE_CYLINDER)
		ret = scene_add_cylinder(scene, obj.data.cylinder);
	else if (obj.type == TYPE_CONE)
		ret = scene_add_cone(scene, obj.data.cone);
	else if (obj.type == TYPE_LIGHT)
		ret = scene_add_light(scene, obj.data.light);
	else if (obj.type == TYPE_CAMERA)
		scene->camera = obj.data.camera;
	else if (obj.type == TYPE_AMBIENT)
		scene->ambient = obj.data.ambient;
	else if (obj.type == TYPE_ANIM || obj.type == TYPE_MESH)
	{
		if (ext && ft_strcmp(ext, ".fbx") == 0)
			ret = parse_fbx(obj.data.mesh_info.path, scene);
		else if (ext && ft_strcmp(ext, ".obj") == 0)
			ret = parse_obj(obj.data.mesh_info.path, scene);
		else if (ext && ft_strcmp(ext, ".fdf") == 0)
			ret = parse_fdf(obj.data.mesh_info.path, scene);
		if (ret)
		{
			if (obj.type == TYPE_ANIM && scene->anim_count > 0)
			{
				anim = &scene->animated[scene->anim_count - 1];
				anim->transform = obj.data.mesh_info.transform;
			}
			else if (obj.type == TYPE_MESH && scene->mesh_count > 0)
			{
				mesh = &scene->meshes[scene->mesh_count - 1];
				mesh->transform = obj.data.mesh_info.transform;
			}
		}
		free(obj.data.mesh_info.path);
	}
	return (ret);
}

bool	parse_rt(const char *path, t_scene *scene)
{
	int		fd;
	char	*line;
	bool	status;

	status = true;
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		return (false);
	}
	while ((line = get_next_line(fd)))
	{
		if (!process_line(scene, line))
			status = false;
		free(line);
		if (!status)
			break ;
	}
	close(fd);
	return (status);
}
