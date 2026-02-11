/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 11:45:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/11 11:45:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "core.h"
# include "debug.h"
# include "objects.h"

# include "scene.h"

typedef struct s_parser
{
	int		fd;
	char	buffer[PARSER_BUF_SIZE + 1];
	size_t	cursor;
	size_t	bytes_read;
	bool	eof;
}	t_parser;

/* Core functions */
void	parser_init(t_parser *p, int fd);
char	parser_peek(t_parser *p);
void	parser_advance(t_parser *p);
void	parser_skip_whitespace(t_parser *p);
bool	parser_match(t_parser *p, char expected);
bool	parser_get_line(t_parser *p, char *buf, size_t max_len);

/* Extractors */
int		parse_int(t_parser *p);
double	parse_double(t_parser *p);
bool	parse_vec3(t_parser *p, t_vec3 *out);

/* JSON Minimal (S7) */
char	*json_find_key(char *json, const char *key);
int		json_get_int(char *json, const char *key);

#endif
