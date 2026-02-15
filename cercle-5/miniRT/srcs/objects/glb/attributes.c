/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attributes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/12 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

static void	fill_attribute_vec3(char *json, char *bin, t_vec3 *dst, int id)
{
	t_accessor		acc;
	t_buffer_view	bv;
	float			*tmp;
	int				i;

	glb_parse_accessor(json, id, &acc);
	glb_parse_buffer_view(json, acc.buffer_view, &bv);
	tmp = malloc(sizeof(float) * 3 * acc.count);
	if (!tmp)
		return ;
	glb_extract_data((t_extract_ctx){bin, &acc, &bv, tmp,
		sizeof(float) * 3, acc.count, sizeof(float) * 3});
	i = -1;
	while (++i < acc.count)
		dst[i] = vec3(tmp[i * 3], tmp[i * 3 + 1], tmp[i * 3 + 2]);
	free(tmp);
}

static void	fill_attribute_vec2(char *json, char *bin, t_vec2 *dst, int id)
{
	t_accessor		acc;
	t_buffer_view	bv;
	float			*tmp;
	int				i;

	glb_parse_accessor(json, id, &acc);
	glb_parse_buffer_view(json, acc.buffer_view, &bv);
	tmp = malloc(sizeof(float) * 2 * acc.count);
	if (!tmp)
		return ;
	glb_extract_data((t_extract_ctx){bin, &acc, &bv, tmp,
		sizeof(float) * 2, acc.count, sizeof(float) * 2});
	i = -1;
	while (++i < acc.count)
		dst[i] = vec2(tmp[i * 2], tmp[i * 2 + 1]);
	free(tmp);
}

void	glb_fill_attributes(t_mesh *mesh, char *json, char *bin, int ids[4])
{
	fill_attribute_vec3(json, bin, mesh->vertices, ids[0]);
	if (ids[1] != -1)
		fill_attribute_vec3(json, bin, mesh->normals, ids[1]);
	if (ids[2] != -1)
		fill_attribute_vec2(json, bin, mesh->uvs, ids[2]);
}
