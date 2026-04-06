/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 10:16:43 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "surface.h"
#include "scene.h"
#include "debug.h"

/**
 * Auto-detects the FDF rendering mode from the file path.
 * Files under generated_maps/ use picture mode (flat + hex color as pixel).
 * All others use height-gradient mode.
 */
t_fdf_mode	fdf_detect_mode(const char *path)
{
	if (ft_strnstr(path, "generated_maps", ft_strlen(path)))
		return (FDF_MODE_PICTURE);
	return (FDF_MODE_HEIGHT_GRADIENT);
}

/*
** Writes an RGB triplet in BGRA format into a 32-bpp pixel buffer.
** texel_at() reads *(unsigned int*)px and extracts (R=byte2, G=byte1, B=byte0).
*/
static void	write_bgra(unsigned char *buf, int idx, int r, int g, int b)
{
	buf[idx * 4 + 0] = (unsigned char)b;
	buf[idx * 4 + 1] = (unsigned char)g;
	buf[idx * 4 + 2] = (unsigned char)r;
	buf[idx * 4 + 3] = 0xFF;
}

/*
** Builds a 256x1 gradient texture:
**   0-63:   Blue  (0,0,255)  → Cyan  (0,255,255)
**  64-127:  Cyan  (0,255,255)→ Green (0,255,0)
** 128-191:  Green (0,255,0)  → Yellow(255,255,0)
** 192-255:  Yellow(255,255,0)→ Red   (255,0,0)
*/
static char	*build_gradient_bitmap(void)
{
	unsigned char	*buf;
	int				i;
	int				t;

	buf = ft_calloc(1, 256 * 4);
	if (!buf)
		return (NULL);
	i = 0;
	while (i < 256)
	{
		t = i % 64;
		if (i < 64)
			write_bgra(buf, i, 0, t * 4, 255);
		else if (i < 128)
			write_bgra(buf, i, 0, 255, 255 - t * 4);
		else if (i < 192)
			write_bgra(buf, i, t * 4, 255, 0);
		else
			write_bgra(buf, i, 255, 255 - t * 4, 0);
		i++;
	}
	return ((char *)buf);
}

/*
** Allocates mesh->uvs (vertex_count entries) and maps each vertex's
** normalized Y height to UV.x in [0,1]. UV.y is fixed at 0.5.
*/
static void	apply_height_uvs(t_mesh *mesh)
{
	size_t	i;
	double	min_y;
	double	max_y;
	double	range;

	min_y = mesh->vertices[0].pos.y;
	max_y = mesh->vertices[0].pos.y;
	i = 1;
	while (i < mesh->vertex_count)
	{
		if (mesh->vertices[i].pos.y < min_y)
			min_y = mesh->vertices[i].pos.y;
		if (mesh->vertices[i].pos.y > max_y)
			max_y = mesh->vertices[i].pos.y;
		i++;
	}
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
	ft_print_debug("FDF HEIGHT: min_y=%.2f max_y=%.2f range=%.2f\n",
		min_y, max_y, range);
}

/*
** Height gradient mode: builds a 256x1 gradient bitmap, applies it to the
** material's albedo_map, and sets per-vertex UVs based on normalized height.
*/
static void	apply_height_gradient(t_mesh *mesh, t_scene *scene)
{
	t_material	*mat;
	char		*bitmap;

	apply_height_uvs(mesh);
	bitmap = build_gradient_bitmap();
	if (!bitmap)
		return ;
	mat = &scene->materials[mesh->mat_id];
	init_texture_props(&mat->albedo_map, 256, 1, bitmap);
	ft_print_debug("FDF HEIGHT: gradient texture applied to mat %zu\n",
		mesh->mat_id);
}

/*
** Builds a W×H bitmap from the raw FDF hex colors stored in fdf->colors.
*/
static char	*build_picture_bitmap(unsigned int *colors, size_t w, size_t h)
{
	unsigned char	*buf;
	size_t			i;
	unsigned int	c;

	buf = ft_calloc(1, w * h * 4);
	if (!buf)
		return (NULL);
	i = 0;
	while (i < w * h)
	{
		c = colors[i];
		write_bgra(buf, i, (c >> 16) & 0xFF, (c >> 8) & 0xFF, c & 0xFF);
		i++;
	}
	return ((char *)buf);
}

/*
** Picture mode: flatten all vertices to Y=0, build a W×H texture from the
** parsed hex colors in fdf->colors, and set grid UV coordinates per vertex.
*/
static void	apply_picture(t_mesh *mesh, t_scene *scene, t_vec2s dims)
{
	size_t			i;
	size_t			w;
	size_t			h;
	unsigned int	*colors;
	t_material		*mat;
	char			*bitmap;

	w = dims.x;
	h = dims.y;
	colors = (unsigned int *)mesh->extra;
	i = 0;
	while (i < mesh->vertex_count)
	{
		mesh->vertices[i].pos.y = 0.0;
		i++;
	}
	bitmap = build_picture_bitmap(colors, w, h);
	if (!bitmap)
		return ;
	mat = &scene->materials[mesh->mat_id];
	init_texture_props(&mat->albedo_map, w, h, bitmap);
	mesh->uvs = malloc(sizeof(t_vec2) * mesh->vertex_count);
	if (!mesh->uvs)
		return ;
	i = 0;
	while (i < mesh->vertex_count)
	{
		mesh->uvs[i].x = (double)(i % w) / (double)(w - 1);
		mesh->uvs[i].y = (double)(i / w) / (double)(h - 1);
		i++;
	}
	ft_print_debug("FDF PICTURE: %zux%zu texture applied to mat %zu\n",
		w, h, mesh->mat_id);
}

/**
 * Applies the selected FDF rendering mode to mesh+material.
 * Frees mesh->extra (raw color buffer) when done.
 */
void	fdf_apply_mode(t_mesh *mesh, t_scene *scene,
	t_vec2s dims, t_fdf_mode mode)
{
	if (mode == FDF_MODE_HEIGHT_GRADIENT)
		apply_height_gradient(mesh, scene);
	else if (mode == FDF_MODE_PICTURE)
		apply_picture(mesh, scene, dims);
	if (mesh->extra)
	{
		free(mesh->extra);
		mesh->extra = NULL;
	}
}
