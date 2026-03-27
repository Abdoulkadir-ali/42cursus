/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ascii_io.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 08:58:36 by abdoali          ###   ########.fr       */
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
	size_t	new_cap;

	while (parser_get_line(p, line, sizeof(line)))
	{
		line_len = ft_strlen(line);
		new_cap = b->len + line_len + 2;
		if (new_cap > b->cap)
		{
			b->cap = (new_cap > b->cap * 2) ? new_cap : b->cap * 2;
			if (b->cap < 1024) b->cap = 1024;
			b->buf = realloc(b->buf, b->cap);
			if (!b->buf) return (false);
		}
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
	ft_memset(&b, 0, sizeof(b));
	if (!io_read_lines(&p, &b))
	{
		free(b.buf);
		close(fd);
		return (NULL);
	}
	close(fd);
	if (!b.buf)
		b.buf = ft_strdup("");
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

/**
 * @brief Parses texture filename from FBX ASCII content.
 * Does not interact with models or scene. (Literal Rule 1).
 */
char	*fbx_ascii_parse_texture_path(char *p, char *end, const char *fbx_p)
{
	char	*node;
	char	*filename;
	char	*full;

	node = find_node(p, end, "Texture:");
	if (!node)
		return (NULL);
	node = find_node(node, end, "FileName:");
	if (!node)
		return (NULL);
	filename = extract_quoted(node, end);
	if (!filename)
		return (NULL);
	full = resolve_fbx_path(fbx_p, filename);
	free(filename);
	return (full);
}
