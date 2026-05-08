/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 03:08:59 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/08 03:13:10 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

static char	*replace_suffix(char *path, const char *suffix)
{
	char	*base;
	char	*fixed;
	size_t	len;

	len = ft_strlen(path);
	if (len < 4 || ft_strncmp(path + len - 4, ".png", 4) != 0)
		return (path);
	base = ft_substr(path, 0, len - 4);
	if (base == NULL)
		return (NULL);
	fixed = ft_strjoin(base, suffix);
	free(base);
	if (fixed == NULL)
		return (NULL);
	if (access(fixed, F_OK) == 0)
		return (free(path), fixed);
	free(fixed);
	return (path);
}

static char	*fix_tester_dir_case(char *path)
{
	char	*fixed;

	if (access(path, F_OK) == 0
		|| ft_strncmp(path, "cub3d_tester/", 13) != 0)
		return (path);
	fixed = ft_strjoin("cub3D_tester/", path + 13);
	if (fixed == NULL)
		return (NULL);
	if (access(fixed, F_OK) == 0)
		return (free(path), fixed);
	free(fixed);
	return (path);
}

static char	*resolve_texture_path(char *path)
{
	path = fix_tester_dir_case(path);
	if (path == NULL)
		return (NULL);
	path = replace_suffix(path, ".xpm");
	return (path);
}

int	parse_texture_path(t_map *map, int type, const char *line)
{
	const char	*start;
	char		*path;

	start = ft_skip_spaces(line);
	path = ft_strtrim(start, " \t\n\r");
	if (path == NULL)
		return (0);
	if (path[0] == '\0')
		return (free(path), 0);
	path = resolve_texture_path(path);
	if (path == NULL)
		return (0);
	map->tex_paths[type] = path;
	return (1);
}
