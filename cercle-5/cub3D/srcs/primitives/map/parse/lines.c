/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 16:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/08 03:00:45 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

int	is_config_line(const char *line)
{
	while (*line != '\0' && ft_isspace(*line) != 0)
		line++;
	if (ft_strncmp(line, "NO", 2) == 0 || ft_strncmp(line, "SO", 2) == 0)
		return (1);
	if (ft_strncmp(line, "WE", 2) == 0 || ft_strncmp(line, "EA", 2) == 0
		|| ft_strncmp(line, "DO", 2) == 0)
		return (1);
	if ((ft_strncmp(line, "R", 1) == 0 || ft_strncmp(line, "S", 1) == 0)
		&& ft_isspace(line[1]) != 0)
		return (1);
	if (ft_strncmp(line, "F", 1) == 0 && ft_isspace(line[1]) != 0)
		return (1);
	if (ft_strncmp(line, "C", 1) == 0 && ft_isspace(line[1]) != 0)
		return (1);
	return (0);
}

int	is_map_line(const char *line)
{
	size_t	i;

	i = 0;
	while (line[i] != '\0' && ft_isspace(line[i]) != 0)
		i++;
	if (line[i] != '\0'
		&& ft_strchr("012NSEWDOdeEGMmPpsA", line[i]) != NULL)
		return (1);
	return (0);
}
