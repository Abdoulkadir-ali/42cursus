/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/13 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

static char	*resolve_fbx_path(const char *fbx_path, const char *tex_filename)
{
	char	*dir;
	char	*full_path;

	dir = path_get_dir(fbx_path);
	if (!dir)
		return (ft_strdup(tex_filename));
	full_path = ft_strjoin(dir, tex_filename);
	free(dir);
	return (full_path);
}

static bool	io_read_lines(t_parser *p, t_fbx_buf *b)
{
	char	line[2048];
	size_t	line_len;

	while (parser_get_line(p, line, sizeof(line)))
	{
		line_len = ft_strlen(line);
		if (!dynarray_ensure((void **)&b->buf, b->len + line_len + 2, &b->cap,
				sizeof(char)))
			return (false);
		ft_memcpy(b->buf + b->len, line, line_len);
		b->len += line_len;
		b->buf[b->len++] = '\n';
	}
	return (true);
}

char	*read_file_content(const char *path, size_t *out_size)
{
	t_parser	p;
	t_fbx_buf	b;
	int			fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	parser_init(&p, fd);
	b.buf = NULL;
	b.cap = 0;
	b.len = 0;
	if (!io_read_lines(&p, &b))
	{
		free(b.buf);
		close(fd);
		return (NULL);
	}
	close(fd);
	if (!b.buf)
	{
		b.buf = ft_strdup("");
		b.len = 0;
	}
	b.buf[b.len] = '\0';
	*out_size = b.len;
	return (b.buf);
}

static char	*extract_quoted(char *p, char *end)
{
	char	*start;
	char	*finish;

	while (p < end && *p && *p != '"')
		p++;
	if (p >= end || *p != '"')
		return (NULL);
	p++;
	start = p;
	while (p < end && *p && *p != '"')
		p++;
	if (p >= end || *p != '"')
		return (NULL);
	finish = p;
	return (ft_substr(start, 0, finish - start));
}

int	parse_texture(char *p, char *end, t_scene *scene, const char *fbx_path)
{
	char	*node;
	char	*filename;
	char	*full_path;
	int		mat_id;

	node = find_node(p, end, "Texture:");
	if (!node)
		return (-1);
	node = find_node(node, end, "FileName:");
	if (!node)
		return (-1);
	filename = extract_quoted(node, end);
	if (!filename)
		return (-1);
	full_path = resolve_fbx_path(fbx_path, filename);
	free(filename);
	mat_id = scene_add_named_material(scene, "FBX_Mat");
	if (load_texture_xpm(scene, &scene->materials[mat_id].albedo_map,
			full_path))
		ft_print_debug("FBX Texture Loaded: %s\n", full_path);
	free(full_path);
	return (mat_id);
}
