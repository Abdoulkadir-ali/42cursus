/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 03:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/07 02:07:48 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#define PARSER_BUF_SIZE 4096

static int	grow_content(t_parser *parser, size_t needed, size_t *capacity)
{
	char	*new_content;
	size_t	new_capacity;

	new_capacity = *capacity;
	if (new_capacity == 0)
		new_capacity = PARSER_BUF_SIZE;
	while (new_capacity < needed)
		new_capacity *= 2;
	new_content = malloc(new_capacity + 1);
	if (new_content == NULL)
		return (0);
	if (parser->full_content != NULL)
		ft_memcpy(new_content, parser->full_content, parser->len);
	free(parser->full_content);
	parser->full_content = new_content;
	*capacity = new_capacity;
	return (1);
}

static int	append_chunk(t_parser *parser, char *buffer, ssize_t bytes_read,
		size_t *capacity)
{
	size_t	needed;

	needed = parser->len + (size_t)bytes_read;
	if (needed >= *capacity && grow_content(parser, needed, capacity) == 0)
		return (0);
	ft_memcpy(parser->full_content + parser->len, buffer, (size_t)bytes_read);
	parser->len = needed;
	parser->full_content[parser->len] = '\0';
	return (1);
}

static int	load_content(t_parser *parser, const char *path)
{
	int			fd;
	ssize_t		bytes_read;
	char		buffer[PARSER_BUF_SIZE];
	size_t		capacity;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	capacity = 0;
	bytes_read = read(fd, buffer, PARSER_BUF_SIZE);
	while (bytes_read > 0)
	{
		if (append_chunk(parser, buffer, bytes_read, &capacity) == 0)
			return (free(parser->full_content), close(fd), 0);
		bytes_read = read(fd, buffer, PARSER_BUF_SIZE);
	}
	close(fd);
	if (bytes_read < 0)
		return (free(parser->full_content), parser->full_content = NULL, 0);
	return (1);
}

int	parser_init(t_parser *parser, const char *path)
{
	if (!parser || !path)
		return (0);
	parser->full_content = NULL;
	parser->len = 0;
	parser->pos = 0;
	parser->eof = false;
	if (!load_content(parser, path))
		return (0);
	return (1);
}

void	parser_close(t_parser *parser)
{
	if (!parser)
		return ;
	if (parser->full_content)
	{
		free(parser->full_content);
		parser->full_content = NULL;
	}
	parser->pos = 0;
	parser->len = 0;
	parser->eof = true;
}
