/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 02:11:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 02:15:59 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "scene.h"
#include "fdf.h"

static int	fdf_check_row(int row_n, int *w, int *h)
{
	if (row_n < 0)
		return (-1);
	if (row_n > 0)
	{
		if (*w < 0)
			*w = row_n;
		else if (row_n != *w)
		{
			fprintf(stderr, "Error\nfdf: ragged row\n");
			return (-1);
		}
		(*h)++;
	}
	return (0);
}

static int	fdf_parse_grid(char *buf, t_fdf_grid *g)
{
	char	*line;
	char	*save;
	int		count;
	int		cap;

	cap = 4096;
	count = 0;
	g->w = -1;
	g->h = 0;
	g->z = (float *)malloc(sizeof(float) * cap);
	if (!g->z)
		return (-1);
	line = strtok_r(buf, "\n", &save);
	while (line)
	{
		if (fdf_check_row(fdf_parse_row(line, &g->z, &count, &cap),
				&g->w, &g->h) < 0)
			return (-1);
		line = strtok_r(NULL, "\n", &save);
	}
	return (0);
}

int	mesh_load_fdf(t_scene *s, const char *path, t_mesh_conf *c)
{
	char		*buf;
	t_fdf_grid	g;
	int			base;

	buf = read_file_all(path);
	if (!buf)
		return (fprintf(stderr, "Error\nfdf: cannot read %s\n", path), -1);
	if (fdf_parse_grid(buf, &g) < 0)
		return (free(buf), free(g.z), -1);
	free(buf);
	if (g.w < 2 || g.h < 2)
		return (free(g.z), fprintf(stderr, "Error\nfdf: too small\n"), -1);
	base = s->n_bvh;
	if (fdf_gen_mesh(s, &g, c) < 0)
		return (free(g.z), -1);
	free(g.z);
	fdf_group_objs(s, base, path);
	return (0);
}
