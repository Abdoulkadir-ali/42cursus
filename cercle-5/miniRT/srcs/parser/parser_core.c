/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_core.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 18:30:00 by abdoali           #+#    #+#             */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include <stdio.h>

void	parser_init(t_parser *p, int fd)
{
	ssize_t	n;

	if (!p)
	{
		fprintf(stderr, "Error: parser_init received NULL pointer\n");
		fflush(stdout);
		return ;
	}
	p->fd = fd;
	p->cursor = 0;
	p->bytes_read = 0;
	p->eof = false;
	ft_memset(p->buffer, 0, PARSER_BUF_SIZE + 1);
	n = read(p->fd, p->buffer, PARSER_BUF_SIZE);
	if (n < 0)
	{
		fprintf(stderr, "Error: parser_init read() error\n");
		p->bytes_read = 0;
		p->eof = true;
	}
	else
	{
		p->bytes_read = (size_t)n;
		if (p->bytes_read < PARSER_BUF_SIZE)
			p->eof = true;
	}
	if (p->bytes_read > 0)
		p->buffer[p->bytes_read] = '\0';
}

static void	ensure_data(t_parser *p)
{
	ssize_t	n;

	if (p->cursor >= p->bytes_read && !p->eof)
	{
		p->cursor = 0;
		n = read(p->fd, p->buffer, PARSER_BUF_SIZE);
		if (n <= 0)
		{
			p->bytes_read = 0;
			p->eof = true;
		}
		else
		{
			p->bytes_read = (size_t)n;
			p->buffer[p->bytes_read] = '\0';
			if (p->bytes_read < PARSER_BUF_SIZE)
				p->eof = true;
		}
	}
}

char	parser_peek(t_parser *p)
{
	ensure_data(p);
	if (p->cursor >= p->bytes_read)
		return (0);
	return (p->buffer[p->cursor]);
}

void	parser_advance(t_parser *p)
{
	if (p->cursor < p->bytes_read)
		p->cursor++;
	ensure_data(p);
}

void	parser_skip_whitespace(t_parser *p)
{
	char	c;
	int		count = 0;

	c = parser_peek(p);
	while (c)
	{
		if (ft_isspace(c))
		{
			parser_advance(p);
			c = parser_peek(p);
			count++;
			if (count > 1000000)
			{
				printf("CRITICAL ERROR: Infinite loop detected in parser_skip_whitespace!\n");
				fflush(stdout);
				break ;
			}
		}
		else
			break ;
	}
}

bool	parser_match(t_parser *p, char expected)
{
	parser_skip_whitespace(p);
	if (parser_peek(p) == expected)
	{
		parser_advance(p);
		return (true);
	}
	return (false);
}

/**
 * Reads a line from the parser into a buffer.
 * Stops at newline or end of file.
 * Returns true if anything was read.
 */
bool	parser_get_line(t_parser *p, char *buf, size_t max_len)
{
	size_t	i;
	char	c;

	i = 0;
	c = parser_peek(p);
	if (!c && p->eof)
		return (false);
	while (c && c != '\n' && c != '\r' && i < max_len - 1)
	{
		buf[i++] = c;
		parser_advance(p);
		c = parser_peek(p);
	}
	if (c == '\r')
	{
		parser_advance(p);
		c = parser_peek(p);
	}
	if (c == '\n')
		parser_advance(p);
	buf[i] = '\0';
	return (true);
}
