/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 06:17:49 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 06:17:50 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	read_buffer(t_parser *p)
{
	ssize_t	n;

	n = read(p->fd, p->buffer, PARSER_BUF_SIZE);
	if (n <= 0)
	{
		p->bytes_read = 0;
		p->eof = true;
		return ;
	}
	p->bytes_read = (size_t)n;
	p->buffer[p->bytes_read] = '\0';
	if (p->bytes_read < PARSER_BUF_SIZE)
		p->eof = true;
}

void	parser_init(t_parser *p, int fd)
{
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
	read_buffer(p);
}

static void	ensure_data(t_parser *p)
{
	if (p->cursor >= p->bytes_read && !p->eof)
	{
		p->cursor = 0;
		read_buffer(p);
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
