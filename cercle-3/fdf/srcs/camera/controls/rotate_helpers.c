/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 05:18:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/22 05:20:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"

static void	init_rot_ctx(t_rot_ctx *c, t_camera *cam)
{
	if (!c || !cam)
		return ;
	c->rot = create_vec3d(cam->rotation.x, cam->rotation.y, cam->rotation.z);
	c->cosv = create_vec3d(cos(c->rot.x), cos(c->rot.y), cos(c->rot.z));
	c->sinv = create_vec3d(sin(c->rot.x), sin(c->rot.y), sin(c->rot.z));
}

void	update_rotation_matrix_helper(t_camera *cam)
{
	t_rot_ctx	ctx;

	if (!cam)
		return ;
	init_rot_ctx(&ctx, cam);
	compose_rotation_matrix_helper(cam, &ctx);
}
