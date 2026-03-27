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

#include "loader.h"

bool	obj_finalize_mesh_to_scene(t_obj_ctx *ctx, t_scene *scene, const char *path)
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
	mesh.mat_id = mat_idx;
	obj_free_ctx(ctx);
	return (scene_add_mesh(scene, mesh));
}
