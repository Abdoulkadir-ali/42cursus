/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 18:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/08 03:13:08 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "parser.h"

static int	parse_xpm_value(const char **ptr)
{
	int	value;

	*ptr = ft_skip_spaces(*ptr);
	if (!ft_isdigit(**ptr))
		return (-1);
	value = 0;
	while (ft_isdigit(**ptr) != 0)
		value = value * 10 + (*((*ptr)++) - '0');
	*ptr = ft_skip_spaces(*ptr);
	return (value);
}

static int	parse_xpm_header_line(const char *line)
{
	const char	*ptr;
	int			dims[4];

	if (!line || *line != '"')
		return (0);
	ptr = line + 1;
	dims[0] = parse_xpm_value(&ptr);
	dims[1] = parse_xpm_value(&ptr);
	ptr = ft_skip_spaces(ptr);
	dims[2] = parse_xpm_value(&ptr);
	dims[3] = parse_xpm_value(&ptr);
	while (*ptr && *ptr != '"')
		ptr++;
	if (*ptr != '"' || dims[0] < 0 || dims[1] < 0 || dims[2] < 0 || dims[3] < 0)
		return (0);
	return (dims[0] > 0 && dims[1] > 0 && dims[2] > 0 && dims[3] > 0);
}

int	validate_xpm_file(const char *path)
{
	t_parser	parser;
	char		*line;
	int			valid;

	if (!parser_init(&parser, path))
		return (0);
	line = NULL;
	valid = 0;
	while (parser_read_line_alloc(&parser, &line))
	{
		if (line[0] == '"')
		{
			valid = parse_xpm_header_line(line);
			free(line);
			break ;
		}
		free(line);
		line = NULL;
	}
	parser_close(&parser);
	return (valid);
}
