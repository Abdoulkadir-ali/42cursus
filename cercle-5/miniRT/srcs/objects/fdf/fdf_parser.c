/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 18:00:00 by abdoali           #+#    #+#             */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

/**
 * Counts the number of columns in a line by splitting by space.
 */
static int	count_columns(char *line)
{
	char	**tokens;
	int		count;

	if (!line)
		return (0);
	tokens = ft_split(line, ' ');
	if (!tokens)
		return (0);
	count = 0;
	while (tokens[count])
	{
		if (ft_isdigit(tokens[count][0]) || tokens[count][0] == '-' \
			|| tokens[count][0] == '+')
			count++;
		else
			break ;
	}
	free_split(tokens);
	return (count);
}

/**
 * Reads the FDF file to determine grid width and height.
 */
static bool	fdf_get_dimensions(const char *path, int *w, int *h)
{
	int		fd;
	char	*line;
	int		cols;

	if ((fd = open(path, O_RDONLY)) < 0)
		return (false);
	(void)(*h = 0, *w = -1);
	while ((line = get_next_line(fd)))
	{
		cols = count_columns(line);
		free(line);
		if (cols == 0)
			continue ;
		if (*w == -1)
			*w = cols;
		else if (*w != cols)
			return (close(fd), false);
		(*h)++;
	}
	close(fd);
	return (*w > 0 && *h > 0);
}

/**
 * Fills the mesh vertex array with data from the FDF file.
 */
static void	fdf_fill_data(const char *path, t_mesh *mesh, int w, int h)
{
	int		fd;
	char	*line;
	char	**tokens;
	int		p[2];

	if ((fd = open(path, O_RDONLY)) < 0)
		return ;
	p[1] = -1;
	while ((line = get_next_line(fd)) && ++p[1] < h)
	{
		tokens = ft_split(line, ' ');
		free(line);
		if (!tokens || !tokens[0] || (!ft_isdigit(tokens[0][0]) \
			&& tokens[0][0] != '-' && tokens[0][0] != '+'))
			(void)(free_split(tokens), p[1]--);
		else
		{
			p[0] = -1;
			while (tokens[++p[0]] && p[0] < w)
				(void)(mesh->vertices[p[1] * w + p[0]] = vec3(p[0] - w / 2.0, \
					ft_atoi(tokens[p[0]]) * 0.2, p[1] - h / 2.0));
			free_split(tokens);
		}
	}
	close(fd);
}

/**
 * Computes average normals for each vertex in the grid.
 */
static void	fdf_compute_normals(t_mesh *mesh, int w, int h)
{
	int		x;
	int		z;
	int		idx;
	t_vec3	v[4];

	z = -1;
	while (++z < h)
	{
		x = -1;
		while (++x < w)
		{
			idx = z * w + x;
			v[0] = (x > 0) ? mesh->vertices[idx - 1] : mesh->vertices[idx];
			v[1] = (x < w - 1) ? mesh->vertices[idx + 1] : mesh->vertices[idx];
			v[2] = (z > 0) ? mesh->vertices[idx - w] : mesh->vertices[idx];
			v[3] = (z < h - 1) ? mesh->vertices[idx + w] : mesh->vertices[idx];
			mesh->normals[idx] = vec3_norm(vec3(v[0].y - v[1].y, 2.0, \
				v[2].y - v[3].y));
		}
	}
}

/**
 * Maps vertices to [0, 1] range for UV coordinates.
 */
static void	fdf_compute_uvs(t_mesh *mesh, int w, int h)
{
	int	i;

	i = 0;
	while (i < w * h)
	{
		mesh->uvs[i].x = (mesh->vertices[i].x + w / 2.0) / (double)w;
		mesh->uvs[i].y = (mesh->vertices[i].z + h / 2.0) / (double)h;
		i++;
	}
}

/**
 * Generates triangle indices for the heightmap grid.
 */
static void	fdf_triangulate(t_mesh *mesh, int w, int h)
{
	int	p[4];
	int	idx;

	p[3] = 0;
	p[1] = -1;
	while (++p[1] < h - 1)
	{
		p[0] = -1;
		while (++p[0] < w - 1)
		{
			idx = p[1] * w + p[0];
			mesh->indices[p[3]++] = idx;
			mesh->indices[p[3]++] = idx + w;
			mesh->indices[p[3]++] = idx + 1;
			mesh->indices[p[3]++] = idx + 1;
			mesh->indices[p[3]++] = idx + w;
			mesh->indices[p[3]++] = idx + w + 1;
		}
	}
}

/**
 * Helper to allocate mesh and initialize it to zero.
 */
static bool	fdf_init_mesh(t_mesh *mesh, int v_count, int i_count, const char *p)
{
	ft_memset(mesh, 0, sizeof(t_mesh));
	mesh->vertices = ft_calloc(v_count, sizeof(t_vec3));
	mesh->normals = ft_calloc(v_count, sizeof(t_vec3));
	mesh->uvs = ft_calloc(v_count, sizeof(t_vec2));
	mesh->indices = ft_calloc(i_count, sizeof(int));
	if (!mesh->vertices || !mesh->normals || !mesh->uvs || !mesh->indices)
	{
		(free(mesh->vertices), free(mesh->normals), free(mesh->uvs), \
			free(mesh->indices));
		return (false);
	}
	mesh->name = ft_strdup(p);
	mesh->tri_count = i_count / 3;
	return (true);
}

/**
 * Main parser for FDF files. Converts heightmap to mesh.
 */
bool	parse_fdf(const char *path, t_scene *scene)
{
	t_mesh	mesh;
	int		v[4];

	if (!fdf_get_dimensions(path, &v[0], &v[1]))
		return (false);
	if (!fdf_init_mesh(&mesh, v[0] * v[1], (v[0] - 1) * (v[1] - 1) * 6, path))
		return (false);
	fdf_fill_data(path, &mesh, v[0], v[1]);
	fdf_compute_normals(&mesh, v[0], v[1]);
	fdf_compute_uvs(&mesh, v[0], v[1]);
	fdf_triangulate(&mesh, v[0], v[1]);
	mesh_build_bvh(&mesh);
	if (!scene_add_mesh(scene, mesh))
	{
		(free(mesh.name), free(mesh.vertices), free(mesh.normals), \
			free(mesh.uvs), free(mesh.indices));
		return (false);
	}
	return (true);
}
