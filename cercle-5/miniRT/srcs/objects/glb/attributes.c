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
	t_extract_ctx	ctx;

	glb_parse_accessor(json, id, &acc);
	glb_parse_buffer_view(json, acc.buffer_view, &bv);
	ctx = (t_extract_ctx){bin, &acc, &bv, dst, sizeof(t_vec3),
		acc.count, sizeof(float) * 3};
	glb_extract_data(ctx);
}

static void	fill_attribute_vec2(char *json, char *bin, t_vec2 *dst, int id)
{
	t_accessor		acc;
	t_buffer_view	bv;
	t_extract_ctx	ctx;

	glb_parse_accessor(json, id, &acc);
	glb_parse_buffer_view(json, acc.buffer_view, &bv);
	ctx = (t_extract_ctx){bin, &acc, &bv, dst, sizeof(t_vec2),
		acc.count, sizeof(float) * 2};
	glb_extract_data(ctx);
}

void	glb_fill_attributes(t_mesh *mesh, char *json, char *bin, int ids[4])
{
	fill_attribute_vec3(json, bin, mesh->vertices, ids[0]);
	if (ids[1] != -1)
		fill_attribute_vec3(json, bin, mesh->normals, ids[1]);
	if (ids[2] != -1)
		fill_attribute_vec2(json, bin, mesh->uvs, ids[2]);
}
