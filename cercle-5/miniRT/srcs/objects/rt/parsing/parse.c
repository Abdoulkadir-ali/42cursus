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
#include "parser.h"

// Helper to read a token (identifier or path) from parser into a buffer
static bool	parse_token(t_parser *p, char *buf, size_t max_len)
{
	size_t	i;
	char	c;

	parser_skip_whitespace(p);
	i = 0;
	c = parser_peek(p);
	if (!c)
		return (false);
	while (c && !ft_isspace(c) && i < max_len - 1)
	{
		buf[i++] = c;
		parser_advance(p);
		c = parser_peek(p);
	}
	buf[i] = '\0';
	return (i > 0);
}

/**
 * Parses a mesh entry from the buffered parser.
 * Order: Path, Position, Rotation, Scale, [Color]
 */
t_parse_obj	parse_mesh_entry(t_parser *p, t_type type)
{
	t_parse_obj	obj;
	t_vec3		rot;
	double		s;
	char		path[1024];

	obj.type = TYPE_NONE;
	printf("DEBUG: Starting parse_mesh_entry\n");
	fflush(stdout);
	if (!parse_token(p, path, 1024))
	{
		printf("DEBUG ERR: Failed to parse mesh path\n");
		fflush(stdout);
		return (obj);
	}
	printf("DEBUG: Mesh path parsed: %s\n", path);
	fflush(stdout);
	obj.type = type;
	obj.data.mesh_info.path = ft_strdup(path);
	obj.data.mesh_info.color = vec3(255, 255, 255);
	
	/* 1. Position */
	if (!parse_vec3(p, &obj.data.mesh_info.transform.pos)) {
		printf("DEBUG ERR: Failed to parse mesh position\n");
		return (free(obj.data.mesh_info.path), (obj.type = TYPE_NONE), obj);
	}
	
	/* 2. Rotation */
	if (!parse_vec3(p, &rot)) {
		printf("DEBUG ERR: Failed to parse mesh rotation\n");
		return (free(obj.data.mesh_info.path), (obj.type = TYPE_NONE), obj);
	}
	obj.data.mesh_info.transform.rotation = (t_rotator){rot.x, rot.y, rot.z};

	/* 3. Scale (can be uniform double or vec3) */
	parser_skip_whitespace(p);
	char c = parser_peek(p);
	if ((c >= '0' && c <= '9') || c == '-' || c == '.')
	{
		if (parse_vec3(p, &obj.data.mesh_info.transform.scale))
			;
		else
		{
			s = parse_double(p);
			obj.data.mesh_info.transform.scale = vec3(s, s, s);
		}
	}
	else
		obj.data.mesh_info.transform.scale = vec3(1, 1, 1);

	/* 4. Optional Color */
	parser_skip_whitespace(p);
	if (parser_peek(p) && parser_peek(p) != '\n')
		parse_vec3(p, &obj.data.mesh_info.color);
	return (obj);
}

static t_parse_obj dispatch_scan(t_parser *p, char *id)
{
    t_parse_obj obj;

    obj.type = TYPE_NONE;
	if (ft_strcmp(id, "A") == 0)
		obj = parse_ambient(p);
	else if (ft_strcmp(id, "C") == 0)
		obj = parse_camera(p);
	else if (ft_strcmp(id, "L") == 0)
		obj = parse_light(p);
	else if (ft_strcmp(id, "sp") == 0)
		obj = parse_sphere(p);
	else if (ft_strcmp(id, "pl") == 0)
		obj = parse_plane(p);
	else if (ft_strcmp(id, "cy") == 0)
		obj = parse_cylinder(p);
	else if (ft_strcmp(id, "cn") == 0)
		obj = parse_cone(p);
	else if (ft_strcmp(id, "sl") == 0)
		obj = parse_spot_light(p);
	else if (ft_strcmp(id, "fbx") == 0)
		obj = parse_mesh_entry(p, TYPE_ANIM);
	else if (ft_strcmp(id, "obj") == 0 || ft_strcmp(id, "fdf") == 0 \
		|| ft_strcmp(id, "glb") == 0 || ft_strcmp(id, "m") == 0)
		obj = parse_mesh_entry(p, TYPE_MESH);
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
	int				mat_id;

	ret = false;
	printf("DEBUG: handle_mesh_injection for %s with ext %s\n", obj->data.mesh_info.path, ext ? ext : "NULL");
	fflush(stdout);
	printf("DEBUG: calling validate_file for %s\n", obj->data.mesh_info.path);
	fflush(stdout);
	if (!validate_file(obj->data.mesh_info.path))
	{
		printf("DEBUG ERR: File not found or invalid: %s\n", obj->data.mesh_info.path);
		return (false);
	}
	printf("DEBUG: validate_file passed, checking extension: %s\n", ext ? ext : "NONE");
	fflush(stdout);
	if (ext && ft_strcmp(ext, ".fbx") == 0)
	{
		printf("DEBUG: calling parse_fbx\n"); fflush(stdout);
		ret = parse_fbx(obj->data.mesh_info.path, scene);
		printf("DEBUG: parse_fbx returned %d\n", ret); fflush(stdout);
	}
	else if (ext && ft_strcmp(ext, ".obj") == 0)
		ret = parse_obj(obj->data.mesh_info.path, scene);
	else if (ext && ft_strcmp(ext, ".fdf") == 0)
		ret = parse_fdf(obj->data.mesh_info.path, scene);
	else if (ext && ft_strcmp(ext, ".glb") == 0)
		ret = parse_glb(obj->data.mesh_info.path, scene);
	
	if (!ret)
	{
		printf("DEBUG ERR: Failed to parse specific format for %s\n", obj->data.mesh_info.path);
		return (false);
	}
	mat_id = scene_add_material(scene, obj->data.mesh_info.color);
	if (obj->type == TYPE_ANIM && scene->anim_count > 0)
	{
		anim = &scene->animated[scene->anim_count - 1];
		anim->base.transform = obj->data.mesh_info.transform;
		mesh_apply_transform(&anim->base, anim->base.transform);
		/* Only override material if it's solid or not set */
		if (anim->base.mat_id <= 0 || scene->materials[anim->base.mat_id].albedo_map.type == TEX_SOLID)
			anim->base.mat_id = mat_id;
	}
	else if (obj->type == TYPE_MESH && scene->mesh_count > 0)
	{
		mesh = &scene->meshes[scene->mesh_count - 1];
		mesh->transform = obj->data.mesh_info.transform;
		mesh_apply_transform(mesh, mesh->transform);
		/* Only override material if it's not already set by the mesh parser (e.g. MTL) */
		printf("DEBUG: Mesh mat_id before override: %d (type %d)\n", mesh->mat_id, scene->materials[mesh->mat_id].albedo_map.type);
		if (scene->materials[mesh->mat_id].albedo_map.type != TEX_BITMAP)
		{
			mesh->mat_id = mat_id;
			printf("DEBUG: Mesh mat_id overridden to %d\n", mat_id);
		}
		else
			printf("DEBUG: Mesh mat_id KEPT as %d (is BITMAP)\n", mesh->mat_id);
	}
	return (true);
}

static bool process_object(t_scene *scene, t_parse_obj obj)
{
    bool ret = true;
    const char *ext;

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
 * Main entrance for parsing .rt files using buffered parser.
 */
bool	parse_rt(const char *path, t_scene *scene)
{
	t_parser    *p;
    int         fd;
    char        id[16];
    t_parse_obj obj;
    bool        status;

	printf("DEBUG: parse_rt size of t_parse_obj: %zu, size of t_parser: %zu\n", sizeof(t_parse_obj), sizeof(t_parser)); fflush(stdout);
	status = true;
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		printf("Error: Could not open .rt file %s\n", path);
		return (false);
	}
	printf("DEBUG: parse_rt opening %s\n", path);
	fflush(stdout);
	p = malloc(sizeof(t_parser));
	if (!p) { close(fd); return (false); }
    parser_init(p, fd);
    
    while (true)
    {
        parser_skip_whitespace(p);
        if (p->eof && p->cursor >= p->bytes_read)
            break;
        if (parser_peek(p) == '#') // Skip comments
        {
            while (parser_peek(p) && parser_peek(p) != '\n')
                parser_advance(p);
            continue;
        }
        if (!parse_token(p, id, 16))
            break;
		printf("DEBUG: dispatch_scan for ID: %s\n", id);
		fflush(stdout);
        obj = dispatch_scan(p, id);
        if (obj.type != TYPE_NONE)
        {
            if (!process_object(scene, obj))
			{
                printf("Error: Failed to process object '%s' in %s\n", id, path);
				status = false;
			}
        }
        else
        {
            printf("Warning: Unknown or invalid object type '%s' in %s\n", id, path);
            // Unknown identifier or error: skip line to prevent infinite loop
            while (parser_peek(p) && parser_peek(p) != '\n')
                parser_advance(p);
			status = false;
        }
    }
	free(p);
	close(fd);
	return (status);
}
