/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 06:17:49 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/29 09:11:36 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/**
 * @brief Reads a chunk from FD into the parser's internal buffer.
 */
static void	read_chunk(t_parser *p)
{
	ssize_t	n;

	if (p->fd < 0 || p->eof)
		return ;
	n = read(p->fd, p->buffer, PARSER_BUF_SIZE);
	if (n <= 0)
	{
		p->bytes_read = 0;
		p->eof = true;
		return ;
	}
	p->bytes_read = (size_t)n;
	p->buffer[n] = '\0';
	if (p->bytes_read < PARSER_BUF_SIZE)
		p->eof = true;
}

/**
 * @brief Standard FD-based parser initialization.
 */
void	parser_init(t_parser *p, int fd)
{
	ft_memset(p, 0, sizeof(t_parser));
	setlocale(LC_NUMERIC, "C");
	p->fd = fd;
	p->buffer = malloc(PARSER_BUF_SIZE + 1);
	if (p->buffer == NULL)
		return ;
	p->is_owned = true;
	p->buffer_sz = PARSER_BUF_SIZE;
	read_chunk(p);
}

/**
 * @brief DOD optimized memory-backed parser initialization.
 * Directly uses the provided string buffer for 100% throughput.
 */
void	parser_init_str(t_parser *p, char *s, size_t sz)
{
	ft_memset(p, 0, sizeof(t_parser));
	p->fd = -1;
	p->buffer = s;
	p->bytes_read = sz;
	p->buffer_sz = sz;
	p->eof = true;
	p->is_owned = false;
}

/**
 * @brief Ensures the buffer has data or reads next chunk if using FD.
 */
static void	ensure_data(t_parser *p)
{
	if (p->cursor >= p->bytes_read && !p->eof && p->fd >= 0)
	{
		p->cursor = 0;
		read_chunk(p);
	}
}

/**
 * @brief Inspects the current character without advancing the cursor.
 */
char	parser_peek(t_parser *p)
{
	ensure_data(p);
	if (p->cursor >= p->bytes_read)
		return ('\0');
	return (p->buffer[p->cursor]);
}

/**
 * @brief Advances the parser cursor by one.
 */
void	parser_advance(t_parser *p)
{
	if (p->cursor < p->bytes_read)
		p->cursor++;
	ensure_data(p);
}

/**
 * @brief Safely releases the parser's internal buffer.
 */
void	parser_free(t_parser *p)
{
	if (p->is_owned && p->buffer != NULL)
		free(p->buffer);
	p->buffer = NULL;
}
