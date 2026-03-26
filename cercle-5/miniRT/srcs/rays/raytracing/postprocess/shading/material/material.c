/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/13 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

static int	dispatch_mat1(t_shading *ctx, int type)
{
	if (type == TYPE_SPHERE)
		return (get_sphere_mat(ctx));
	if (type == TYPE_PLANE)
		return (get_plane_mat(ctx));
	if (type == TYPE_CYLINDER)
		return (get_cylinder_mat(ctx));
	if (type == TYPE_CONE)
		return (get_cone_mat(ctx));
	if (type == TYPE_TRI)
		return (get_tri_mat(ctx));
	if (type == TYPE_RECT)
		return (get_rect_mat(ctx));
	return (-1);
}

static int	dispatch_mat2(t_shading *ctx, int type)
{
	if (type == TYPE_PYRAMID)
		return (get_pyramid_mat(ctx));
	if (type == TYPE_BOX)
		return (get_box_mat(ctx));
	if (type == TYPE_CAPSULE)
		return (get_capsule_mat(ctx));
	if (type == TYPE_MESH)
		return (get_mesh_mat(ctx));
	if (type == TYPE_ANIM)
		return (get_anim_mat(ctx));
	return (-1);
}

void	get_material(t_shading *ctx)
{
	int	mat_id;
	int	type;

	type = ctx->hit->ref.type;
	mat_id = dispatch_mat1(ctx, type);
	if (mat_id == -1)
		mat_id = dispatch_mat2(ctx, type);
	if (mat_id < 0 || mat_id >= ctx->scene->mat_count)
		mat_id = 0;
	ctx->mat = ctx->scene->materials[mat_id];
}
