/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bone_transform.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 09:35:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "animations.h"

void	anim_apply_trs_to_bone(t_bone *bone, t_vec3 pos, t_vec3 rot, t_vec3 scale)
{
	t_mat4	local;

	/* 
	** GLTF order: v' = T * R * S * v
	** In row-major notation: v * S * R * T
	*/
	local = mat4_mul(mat4_scaling(scale), quat_to_mat4(rot));
	local = mat4_mul(local, mat4_translation(pos));
	bone->local_transform = local;
}
