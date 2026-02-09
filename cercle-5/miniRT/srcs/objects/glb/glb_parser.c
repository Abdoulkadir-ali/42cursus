/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glb_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 15:30:00 by abdoali           #+#    #+#             */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

/**
 * Minimal JSON parser helper to find a key.
 */
static char	*json_find_key(char *json, const char *key)
{
	char	*ptr;
	size_t	len;

	if (!json || !key)
		return (NULL);
	len = ft_strlen(key);
	ptr = json;
	while (*ptr)
	{
		ptr = ft_strnstr(ptr, key, ft_strlen(ptr));
		if (!ptr)
			return (NULL);
		if (ptr > json && *(ptr - 1) == '"' && *(ptr + len) == '"')
			return (ptr + len + 1);
		ptr++;
	}
	return (NULL);
}

/**
 * Minimal JSON parser helper to get an integer value.
 */
static int	json_get_int(char *json, const char *key)
{
	char	*ptr;

	if (!json || !key)
		return (-1);
	ptr = json_find_key(json, key);
	if (!ptr)
		return (-1);
	while (*ptr && (*ptr == ':' || *ptr == ' ' || *ptr == '"'))
		ptr++;
	return (ft_atoi(ptr));
}

/**
 * Processes the type string from the JSON accessor entry.
 */
static void	process_type_string(char *ptr, t_accessor *acc)
{
	char	*t;
	int		j;

	t = json_find_key(ptr, "type");
	if (t)
	{
		while (*t && (*t == ':' || *t == ' ' || *t == '"'))
			t++;
		j = 0;
		while (t[j] && t[j] != '"' && j < 15)
		{
			acc->type[j] = t[j];
			j++;
		}
		acc->type[j] = '\0';
	}
}

/**
 * Parses an accessor entry from the JSON chunk.
 */
static void	parse_accessor(char *json, int index, t_accessor *acc)
{
	char	*ptr;
	int		i;

	ptr = json_find_key(json, "accessors");
	if (!ptr)
		return ;
	ptr = ft_strchr(ptr, '[');
	i = 0;
	while (i < index && ptr)
	{
		ptr = ft_strchr(ptr, '}');
		if (ptr)
			ptr++;
		i++;
	}
	if (!ptr)
		return ;
	acc->buffer_view = json_get_int(ptr, "bufferView");
	acc->byte_offset = json_get_int(ptr, "byteOffset");
	acc->component_type = json_get_int(ptr, "componentType");
	acc->count = json_get_int(ptr, "count");
	process_type_string(ptr, acc);
}

/**
 * Parses a buffer view entry from the JSON chunk.
 */
static void	parse_buffer_view(char *json, int index, t_buffer_view *bv)
{
	char	*ptr;
	int		i;

	ptr = json_find_key(json, "bufferViews");
	if (!ptr)
		return ;
	ptr = ft_strchr(ptr, '[');
	i = 0;
	while (i < index && ptr)
	{
		ptr = ft_strchr(ptr, '}');
		if (ptr)
			ptr++;
		i++;
	}
	if (!ptr)
		return ;
	bv->buffer = json_get_int(ptr, "buffer");
	bv->byte_offset = json_get_int(ptr, "byteOffset");
	bv->byte_length = json_get_int(ptr, "byteLength");
	bv->byte_stride = json_get_int(ptr, "byteStride");
	if (bv->byte_stride <= 0)
		bv->byte_stride = 0;
}

/**
 * Extracts binary data from the BIN chunk using accessor and buffer view info.
 */
static void	extract_data(t_extract_ctx ctx)
{
	int		i;
	int		src_stride;
	char	*src;
	char	*dst;

	if (!ctx.bin || !ctx.bv || !ctx.acc || !ctx.entry)
		return ;
	src = ctx.bin + ctx.bv->byte_offset + ctx.acc->byte_offset;
	src_stride = ctx.bv->byte_stride;
	if (src_stride == 0)
		src_stride = ctx.type_size;
	dst = (char *)ctx.entry;
	i = 0;
	while (i < ctx.count)
	{
		ft_memcpy(dst + i * ctx.stride, src + i * src_stride, ctx.type_size);
		i++;
	}
}

/**
 * Helper to handle index conversion from unsigned short to int.
 */
static void	handle_indices_short(t_mesh *mesh, char *json, char *bin, int idx)
{
	t_accessor		acc;
	t_buffer_view	bv;
	t_extract_ctx	ctx;
	unsigned short	*temp;
	int				k;

	parse_accessor(json, idx, &acc);
	parse_buffer_view(json, acc.buffer_view, &bv);
	temp = malloc(sizeof(unsigned short) * acc.count);
	if (!temp)
		return ;
	ctx = (t_extract_ctx){bin, &acc, &bv, temp, sizeof(unsigned short), \
		acc.count, sizeof(unsigned short)};
	extract_data(ctx);
	k = -1;
	while (++k < acc.count)
		mesh->indices[k] = (int)temp[k];
	free(temp);
}

/**
 * Fills vertex attributes (position, normal, uv) from binary data.
 */
static void	fill_attributes(t_mesh *mesh, char *json, char *bin, int ids[4])
{
	t_accessor		acc;
	t_buffer_view	bv;
	t_extract_ctx	ctx;

	parse_accessor(json, ids[0], &acc);
	parse_buffer_view(json, acc.buffer_view, &bv);
	ctx = (t_extract_ctx){bin, &acc, &bv, mesh->vertices, sizeof(t_vec3), \
		acc.count, sizeof(float) * 3};
	extract_data(ctx);
	if (ids[1] != -1)
	{
		parse_accessor(json, ids[1], &acc);
		parse_buffer_view(json, acc.buffer_view, &bv);
		ctx = (t_extract_ctx){bin, &acc, &bv, mesh->normals, sizeof(t_vec3), \
			acc.count, sizeof(float) * 3};
		extract_data(ctx);
	}
	if (ids[2] != -1)
	{
		parse_accessor(json, ids[2], &acc);
		parse_buffer_view(json, acc.buffer_view, &bv);
		ctx = (t_extract_ctx){bin, &acc, &bv, mesh->uvs, sizeof(t_vec2), \
			acc.count, sizeof(float) * 2};
		extract_data(ctx);
	}
}

/**
 * Loads the mesh binary data by parsing the JSON and extracting from the BIN.
 */
static bool	load_mesh_data(t_mesh *mesh, char *json, char *bin)
{
	char			*p[3];
	int				ids[4];
	t_accessor		acc;
	t_buffer_view	bv;

	if (!(p[0] = json_find_key(json, "meshes"))) return (false);
	if (!(p[1] = json_find_key(p[0], "primitives"))) return (false);
	if (!(p[2] = json_find_key(p[1], "attributes"))) return (false);
	ids[0] = json_get_int(p[2], "POSITION");
	ids[1] = json_get_int(p[2], "NORMAL");
	ids[2] = json_get_int(p[2], "TEXCOORD_0");
	ids[3] = json_get_int(p[1], "indices");
	if (ids[0] == -1 || ids[3] == -1) return (false);
	parse_accessor(json, ids[0], &acc);
	mesh->vertices = ft_calloc(acc.count, sizeof(t_vec3));
	mesh->normals = ft_calloc(acc.count, sizeof(t_vec3));
	mesh->uvs = ft_calloc(acc.count, sizeof(t_vec2));
	parse_accessor(json, ids[3], &acc);
	mesh->indices = ft_calloc(acc.count, sizeof(int));
	if (!mesh->vertices || !mesh->indices || !mesh->normals || !mesh->uvs)
		return (false);
	mesh->tri_count = acc.count / 3;
	fill_attributes(mesh, json, bin, ids);
	parse_accessor(json, ids[3], &acc);
	if (acc.component_type == 5123)
		handle_indices_short(mesh, json, bin, ids[3]);
	else
	{
		parse_buffer_view(json, acc.buffer_view, &bv);
		extract_data((t_extract_ctx){bin, &acc, &bv, mesh->indices, \
			sizeof(int), acc.count, sizeof(int)});
	}
	return (true);
}

/**
 * Entry point for GLB (Binary glTF) parser.
 */
bool	parse_glb(const char *path, t_scene *scene)
{
	int				p[2];
	t_glb_header	h;
	t_chunk_header	c[2];
	char			*buf[2];
	t_mesh			mesh;

	if ((p[0] = open(path, O_RDONLY)) < 0 || read(p[0], &h, 12) < 12 \
		|| h.magic != GLB_MAGIC)
		return (close(p[0]), false);
	if (read(p[0], &c[0], 8) < 8 || c[0].type != CHUNK_JSON)
		return (close(p[0]), false);
	buf[0] = ft_calloc(1, c[0].length + 1);
	if (read(p[0], buf[0], c[0].length) < (ssize_t)c[0].length)
		return (free(buf[0]), close(p[0]), false);
	if (read(p[0], &c[1], 8) < 8 || c[1].type != CHUNK_BIN)
		return (free(buf[0]), close(p[0]), false);
	buf[1] = malloc(c[1].length);
	if (read(p[0], buf[1], c[1].length) < (ssize_t)c[1].length)
		return (free(buf[0]), free(buf[1]), close(p[0]), false);
	close(p[0]);
	ft_memset(&mesh, 0, sizeof(mesh));
	mesh.name = ft_strdup(path);
	if (load_mesh_data(&mesh, buf[0], buf[1]))
	{
		(mesh_build_bvh(&mesh), scene_add_mesh(scene, mesh));
		printf("GLB: Loaded %s with %d triangles\n", path, mesh.tri_count);
	}
	else
		(free(mesh.name), free(mesh.vertices), free(mesh.normals), \
			free(mesh.uvs), free(mesh.indices));
	return (free(buf[0]), free(buf[1]), true);
}
