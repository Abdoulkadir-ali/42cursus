/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/09 02:59:36 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	get_height_range(t_mesh *mesh, double *min_y, double *max_y)
{
	size_t	i;

	*min_y = mesh->vertices[0].pos.y;
	*max_y = mesh->vertices[0].pos.y;
	i = 0;
	while (++i < mesh->vertex_count)
	{
		if (mesh->vertices[i].pos.y < *min_y)
			*min_y = mesh->vertices[i].pos.y;
		if (mesh->vertices[i].pos.y > *max_y)
			*max_y = mesh->vertices[i].pos.y;
	}
}

static void	apply_height_uvs(t_mesh *mesh)
{
	size_t	i;
	double	min_y;
	double	max_y;
	double	range;

	get_height_range(mesh, &min_y, &max_y);
	range = max_y - min_y;
	if (range < 1e-9)
		range = 1.0;
	mesh->uvs = malloc(sizeof(t_vec2) * mesh->vertex_count);
	if (!mesh->uvs)
		return ;
	i = 0;
	while (i < mesh->vertex_count)
	{
		mesh->uvs[i].x = (mesh->vertices[i].pos.y - min_y) / range;
		mesh->uvs[i].y = 0.5;
		i++;
	}
}

void	apply_height_gradient(t_mesh *mesh, t_scene *scene)
{
	t_material	*mat;
	char		*bitmap;

	apply_height_uvs(mesh);
	bitmap = build_gradient_bitmap();
	if (!bitmap)
		return ;
	mat = &scene->materials[mesh->mat_id];
	init_texture_props(&mat->albedo_map, 256, 1, bitmap);
}

static void	apply_picture_uvs(t_mesh *mesh, t_vec2s dims)
{
	size_t	i;

	mesh->uvs = malloc(sizeof(t_vec2) * mesh->vertex_count);
	if (!mesh->uvs)
		return ;
	i = 0;
	while (i < mesh->vertex_count)
	{
		mesh->uvs[i].x = (double)(i % dims.x) / (double)(dims.x - 1);
		mesh->uvs[i].y = (double)(i / dims.x) / (double)(dims.y - 1);
		i++;
	}
}

void	apply_picture(t_mesh *mesh, t_scene *scene, t_vec2s dims,
		unsigned int *colors)
{
	size_t			i;
	t_material		*mat;
	char			*bitmap;

	i = 0;
	while (i < mesh->vertex_count)
	{
		mesh->vertices[i].pos.y = 0.0;
		mesh->vertices[i].normal = vec3(0, 1, 0);
		i++;
	}
	bitmap = build_picture_bitmap(colors, dims.x, dims.y);
	if (!bitmap)
		return ;
	mat = &scene->materials[mesh->mat_id];
	init_texture_props(&mat->albedo_map, dims.x, dims.y, bitmap);
	free(mesh->uvs);
	apply_picture_uvs(mesh, dims);
}
