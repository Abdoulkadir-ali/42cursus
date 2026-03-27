/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_dimensions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/12 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"

static int	count_columns(char *line)
{
	int		count;
	char	*p;

	if (!line)
		return (0);
	count = 0;
	p = line;
	while (*p)
	{
		while (*p && ft_isspace(*p))
			p++;
		if (!*p)
			break ;
		if (ft_isdigit(*p) || *p == '-' || *p == '+')
			count++;
		while (*p && !ft_isspace(*p))
			p++;
	}
	return (count);
}

static bool	update_dimensions(int *w, int *h, int cols)
{
	if (cols == 0)
		return (true);
	if (*w == -1)
		*w = cols;
	else if (*w != cols)
		return (false);
	(*h)++;
	return (true);
}

bool	fdf_get_dimensions(const char *path, int *w, int *h)
{
	int			fd;
	t_parser	p;
	int			cols;
	char		line[PARSER_BUF_SIZE + 1];

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (false);
	parser_init(&p, fd);
	*h = 0;
	*w = -1;
	while (parser_get_line(&p, line, PARSER_BUF_SIZE + 1))
	{
		cols = count_columns(line);
		if (!update_dimensions(w, h, cols))
		{
			close(fd);
			return (false);
		}
	}
	close(fd);
	return (*w > 0 && *h > 0);
}
