/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 16:21:10 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/30 22:29:31 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glb.h"

/**
 * Creates a combined S * R * T matrix for a node's local transform.
 */
t_mat4	make_transform(t_vec3 t, t_vec4 r_quat, double scale[3])
{
	t_mat4	mt;
	t_mat4	mr;
	t_mat4	ms;

	mt = mat4_translation(t);
	mr = quat_to_mat4(r_quat);
	ms = mat4_scaling(vec3(scale[0], scale[1], scale[2]));
	return (mat4_mul(ms, mat4_mul(mr, mt)));
}
