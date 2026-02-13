/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finalize_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/12 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

void	obj_free_ctx(t_obj_ctx *ctx)
{
	free(ctx->temp_v);
	free(ctx->temp_vt);
	free(ctx->temp_vn);
}

void	obj_init_mesh(t_mesh *mesh, t_obj_ctx *ctx, const char *path)
{
	ft_memset(mesh, 0, sizeof(t_mesh));
	mesh->name = ft_strdup(path);
	mesh->vertices = ctx->out_v;
	mesh->normals = ctx->out_vn;
	mesh->uvs = ctx->out_vt;
	mesh->indices = ctx->out_i;
	mesh->vertex_count = ctx->out_v_count;
	mesh->tri_count = ctx->out_i_count / 3;
	mesh->bbox = ctx->bbox;
}

void	obj_set_mat_id(t_mesh *mesh, t_obj_ctx *ctx)
{
	mesh->mat_id = 0;
	if (ctx->current_mat_id >= 0)
		mesh->mat_id = ctx->current_mat_id;
}
