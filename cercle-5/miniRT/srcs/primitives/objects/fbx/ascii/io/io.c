/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fbx.h"

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
		b.buf = ft_strdup("");
	b.buf[b.len] = '\0';
	*out_size = b.len;
	return (b.buf);
}
