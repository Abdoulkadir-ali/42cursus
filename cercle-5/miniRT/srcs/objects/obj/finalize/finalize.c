/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_finalize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/12 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

bool	obj_build_mesh(t_scene *scene, t_obj_ctx *ctx, const char *path)
{
	t_mesh	mesh;

	if (ctx->out_v_count == 0)
	{
		obj_free_ctx(ctx);
		return (false);
	}
	obj_generate_normals(ctx);
	obj_init_mesh(&mesh, ctx, path);
	obj_set_mat_id(&mesh, ctx);
	obj_free_ctx(ctx);
	mesh_build_bvh(&mesh);
	scene_add_mesh(scene, mesh);
	return (true);
}
