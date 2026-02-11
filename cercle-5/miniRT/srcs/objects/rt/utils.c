/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/08 14:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

static bool	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\v'
		|| c == '\f' || c == '\r');
}

void	skip_whitespace(char **line)
{
	while (**line && is_space(**line))
		(*line)++;
}

/*
** Parses a float from the substring at *line, advancing the pointer.
*/
bool	parse_float_fast(char **line, double *out)
{
	char	*start;
	char	*endptr;

	skip_whitespace(line);
	start = *line;
	if (!*start)
		return (false);
	*out = strtod(start, &endptr);
	if (endptr == start)
		return (false);
	*line = endptr;
	return (true);
}

/*
** Parses a comma-separated vec3 without splitting.
** Format: x,y,z
*/
bool	parse_vec3_fast(char **line, t_vec3 *out)
{
	t_vec3	v;

	ft_memset(&v, 0, sizeof(t_vec3));
	skip_whitespace(line);
	if (!parse_float_fast(line, &v.x))
		return (false);
	skip_whitespace(line);
	if (**line == ',')
		(*line)++;
	else
		return (false);
	if (!parse_float_fast(line, &v.y))
		return (false);
	skip_whitespace(line);
	if (**line == ',')
		(*line)++;
	else
		return (false);
	if (!parse_float_fast(line, &v.z))
		return (false);
	*out = v;
	return (true);
}

/*
** Parses a color (0-255) into a normalized vec3 (internal use might vary).
** This function expects standard 255-format scaling.
*/
bool	parse_color_fast(char **line, t_vec3 *out)
{
	t_vec3	col;

	if (!parse_vec3_fast(line, &col))
		return (false);
	if (col.x < 0 || col.x > 255 || col.y < 0
		|| col.y > 255 || col.z < 0 || col.z > 255)
		return (false);
	*out = col;
	return (true);
}

char	*get_next_token(char **line)
{
	char	*start;
	char	*token;
	size_t	len;

	skip_whitespace(line);
	start = *line;
	if (!*start)
		return (NULL);
	while (**line && !is_space(**line))
		(*line)++;
	len = *line - start;
	token = malloc(len + 1);
	if (!token)
		return (NULL);
	ft_strlcpy(token, start, len + 1);
	return (token);
}

/* Kept for compatibility but updated to use new helpers if needed */
bool	validate_file(const char *path)
{
	int	fd;

	if (!path || !*path)
		return (false);
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error\nminiRT: ", 2);
		perror(path);
		return (false);
	}
	close(fd);
	return (true);
}

