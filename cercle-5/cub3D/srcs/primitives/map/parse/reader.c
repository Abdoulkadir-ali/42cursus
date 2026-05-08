/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 23:35:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/08 02:59:55 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "parser.h"

static int	add_raw_line(char ***raw, size_t *cap, size_t *count,
		const char *line)
{
	char	**tmp;
	size_t	new_cap;

	if (*cap == 0 || *count >= *cap - 1)
	{
		new_cap = 8;
		if (*cap > 0)
			new_cap = *cap * 2;
		tmp = malloc(sizeof(char *) * (new_cap + 1));
		if (tmp == NULL)
			return (0);
		if (*raw)
		{
			ft_memcpy(tmp, *raw, sizeof(char *) * (*count));
			free(*raw);
		}
		*raw = tmp;
		*cap = new_cap;
	}
	(*raw)[*count] = ft_strdup(line);
	if ((*raw)[*count] == NULL)
		return (0);
	(*count)++;
	(*raw)[*count] = NULL;
	return (1);
}

static int	is_mandatory_done(t_map *map)
{
	return (map->tex_paths[TEX_NO] && map->tex_paths[TEX_SO]
		&& map->tex_paths[TEX_WE] && map->tex_paths[TEX_EA]
		&& (map->tex_paths[TEX_FLOOR] || map->floor_color.x >= 0)
		&& (map->tex_paths[TEX_CEIL] || map->ceil_color.x >= 0));
}

static int	classify_line(t_map *map, char ***raw, t_vec3s *c, char *line)
{
	int	rc;

	if (is_config_line(line) != 0)
	{
		if (c->y > 0)
			return (0);
		rc = parse_config_line(line, map);
		if (rc == 0)
			return (0);
	}
	else if (is_map_line(line) != 0)
	{
		if (!is_mandatory_done(map))
			return (0);
		if (add_raw_line(raw, &c->x, &c->y, line) == 0)
			return (0);
	}
	else if (line[0] != '\0')
		return (0);
	return (1);
}

int	process_line(t_parser *parser, t_map *map, char ***raw,
		t_vec3s *c)
{
	char	*line;
	size_t	i;

	while (parser_read_line_alloc(parser, &line))
	{
		i = 0;
		while (line[i] != '\0' && line[i] != '\n' && line[i] != '\r'
			&& ft_isspace((unsigned char)line[i]) != 0)
			i++;
		if (line[i] == '\0' || line[i] == '\n' || line[i] == '\r'
			|| line[i] == '#')
		{
			if (c->y > 0)
				return (free(line), 0);
			free(line);
			continue ;
		}
		if (classify_line(map, raw, c, line) == 0)
			return (free(line), 0);
		free(line);
	}
	return (is_mandatory_done(map) && c->y > 0);
}
