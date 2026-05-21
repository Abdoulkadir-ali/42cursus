/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 02:06:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 02:06:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "libft.h"
#include "fdf.h"

static int	fdf_realloc(float **zp, int *cap)
{
	float	*tmp;

	*cap *= 2;
	tmp = (float *)realloc(*zp, sizeof(float) * (*cap));
	if (!tmp)
		return (-1);
	*zp = tmp;
	return (0);
}

int	fdf_parse_row(char *line, float **zp, int *count, int *cap)
{
	char	*tok;
	char	*save;
	char	*comma;
	int		c;
	int		ok;

	c = 0;
	tok = strtok_r(line, " \t\r", &save);
	while (tok)
	{
		comma = strchr(tok, ',');
		if (comma)
			*comma = '\0';
		if (*count >= *cap && fdf_realloc(zp, cap) < 0)
			return (-1);
		ok = 0;
		(*zp)[(*count)++] = ft_atof_strict(tok, &ok);
		if (!ok)
			return (-1);
		c++;
		tok = strtok_r(NULL, " \t\r", &save);
	}
	return (c);
}
