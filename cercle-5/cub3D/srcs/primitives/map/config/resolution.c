/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolution.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 03:24:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/08 03:26:31 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

static long long	parse_resolution_value(const char **line, bool *error)
{
	char	buf[32];
	size_t	i;

	*line = ft_skip_spaces(*line);
	i = 0;
	while ((*line)[i] != '\0' && ft_isspace((unsigned char)(*line)[i]) == 0)
	{
		if (i + 1 >= sizeof(buf))
		{
			*error = true;
			return (0);
		}
		buf[i] = (*line)[i];
		i++;
	}
	buf[i] = '\0';
	*line += i;
	return (ft_safe_atoll(buf, error));
}

int	parse_resolution_line(const char *line)
{
	long long	width;
	long long	height;
	bool		error;

	error = false;
	width = parse_resolution_value(&line, &error);
	if (error != false || width < 0)
		return (0);
	height = parse_resolution_value(&line, &error);
	if (error != false || height < 0)
		return (0);
	line = ft_skip_spaces(line);
	return (*line == '\0');
}
