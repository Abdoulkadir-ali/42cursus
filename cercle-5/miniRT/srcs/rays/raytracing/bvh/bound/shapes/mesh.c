/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/13 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

static t_aabb	get_mesh_aabb(t_mesh *mesh)
{
	if (mesh->transform.pos.x == 0
		&& mesh->transform.pos.y == 0
		&& mesh->transform.pos.z == 0
		&& mesh->transform.rotation.pitch == 0
		&& mesh->transform.rotation.yaw == 0
		&& mesh->transform.scale.x == 1
		&& mesh->transform.scale.y == 1
		&& mesh->transform.scale.z == 1)
		return (mesh->bbox);
	return (aabb_transform(mesh->bbox, mesh->transform));
}

static t_aabb	get_anim_aabb(t_anim *anim)
{
	return (aabb_transform(anim->base.bbox, anim->base.transform));
}
