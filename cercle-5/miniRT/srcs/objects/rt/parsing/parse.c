/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 19:17:36 by abdoali           #+#    #+#             */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

/**
 * Dispatches the parsing of a line to the appropriate object parser.
 * 
 * @param tokens The tokens from the split line.
 * @return The parsed object data.
 */
static t_parse_obj	dispatch_parser(char **tokens)
{
	t_parse_obj	obj;

	obj.type = TYPE_NONE;
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
	else if (ft_strcmp(tokens[0], "obj") == 0 || ft_strcmp(tokens[0], "fdf") == 0 \
		|| ft_strcmp(tokens[0], "glb") == 0)
		obj = parse_mesh_entry(tokens, TYPE_MESH);
	return (obj);
}

/**
 * Splits a line and dispatches it to the parser.
 * 
 * @param line The string to parse.
 * @return The parsed object data.
 */
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
	obj = dispatch_parser(tokens);
	free_split(tokens);
	return (obj);
}

/**
 * Handles the injection of parsed mesh files (.fbx, .obj, .fdf, .glb).
 */
static bool	handle_mesh_injection(t_parse_obj *obj, const char *ext, \
	t_scene *scene)
{
	bool			ret;
	t_skinned_mesh	*anim;
	t_mesh			*mesh;

	ret = false;
	if (ext && ft_strcmp(ext, ".fbx") == 0)
		ret = parse_fbx(obj->data.mesh_info.path, scene);
	else if (ext && ft_strcmp(ext, ".obj") == 0)
		ret = parse_obj(obj->data.mesh_info.path, scene);
	else if (ext && ft_strcmp(ext, ".fdf") == 0)
		ret = parse_fdf(obj->data.mesh_info.path, scene);
	else if (ext && ft_strcmp(ext, ".glb") == 0)
		ret = parse_glb(obj->data.mesh_info.path, scene);
	if (ret && obj->type == TYPE_ANIM && scene->anim_count > 0)
	{
		anim = &scene->animated[scene->anim_count - 1];
		anim->base.transform = obj->data.mesh_info.transform;
		printf("Loaded Animated %s at (%.1f, %.1f, %.1f)\n", \
			obj->data.mesh_info.path, anim->base.transform.pos.x, \
			anim->base.transform.pos.y, anim->base.transform.pos.z);
	}
	else if (ret && obj->type == TYPE_MESH && scene->mesh_count > 0)
	{
		mesh = &scene->meshes[scene->mesh_count - 1];
		mesh->transform = obj->data.mesh_info.transform;
		printf("Loaded Mesh %s at (%.1f, %.1f, %.1f)\n", \
			obj->data.mesh_info.path, mesh->transform.pos.x, \
			mesh->transform.pos.y, mesh->transform.pos.z);
	}
	return (ret);
}

/**
 * Processes a single line from the scene file.
 * 
 * @param scene The scene to update.
 * @param line The line string.
 * @return True if successful, false otherwise.
 */
static bool	process_line(t_scene *scene, char *line)
{
	t_parse_obj		obj;
	size_t			len;
	const char		*ext;
	bool			ret;

	if (!line || *line == '\0' || *line == '#')
		return (true);
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	obj = parse_line(line);
	if (obj.type == TYPE_NONE)
		return (true);
	ret = true;
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
		ext = strrchr(obj.data.mesh_info.path, '.');
		ret = handle_mesh_injection(&obj, ext, scene);
		free(obj.data.mesh_info.path);
	}
	return (ret);
}

/**
 * Main entrance for parsing .rt files.
 * 
 * @param path Path to the .rt file.
 * @param scene The scene to fill.
 * @return True if successful, false otherwise.
 */
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
	line = get_next_line(fd);
	while (line)
	{
		if (!process_line(scene, line))
			status = false;
		free(line);
		if (!status)
			break ;
		line = get_next_line(fd);
	}
	close(fd);
	return (status);
}
