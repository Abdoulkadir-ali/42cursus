/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 15:04:49 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/29 19:53:59 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "libft.h"
# include <fcntl.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <unistd.h>

typedef struct s_parser
{
	char	*full_content;
	size_t	pos;
	size_t	len;
	bool	eof;
}			t_parser;

int			parser_init(t_parser *parser, const char *path);
void		parser_close(t_parser *parser);

/* INTERNAL HELPERS */
int			parser_peek_char(t_parser *parser, char *out);
int			parser_next_char(t_parser *parser, char *out);
void		parser_skip_whitespace(t_parser *parser);
int			parser_read_token(t_parser *parser, char *out, size_t max_len);
int			parser_read_int(t_parser *parser, int *value);
int			parser_read_line_alloc(t_parser *parser, char **out);
int			parser_is_eof(t_parser *parser);

#endif
