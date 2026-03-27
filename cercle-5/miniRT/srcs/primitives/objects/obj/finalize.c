/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_finalize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 12:45:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

bool	obj_finalize_mesh_raw(t_obj_ctx *ctx, t_raw_model *model, const char *path)
{
	t_mesh	mesh;
	int		mat_idx;

	if (ctx->out_v_count == 0)
	{
		obj_free_ctx(ctx);
		return (false);
	}
	obj_generate_normals(ctx);
	obj_init_mesh(&mesh, ctx, path);
	mat_idx = ctx->current_mat_id;
	obj_free_ctx(ctx);
	if (dynarray_ensure((void **)&model->meshes, model->mesh_count + 1, NULL, sizeof(t_mesh)))
	{
		model->meshes[model->mesh_count++] = mesh;
		if (dynarray_ensure((void **)&model->mesh_mat_indices, model->mesh_count, NULL, sizeof(int)))
			model->mesh_mat_indices[model->mesh_count - 1] = mat_idx;
	}
	else
	{
		mesh_free(&mesh);
		return (false);
	}
	return (true);
}
