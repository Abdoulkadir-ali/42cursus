/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finalize_normals.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/12 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "obj.h"

static void	add_face_normal(t_obj *obj, size_t i)
{
	int		idx[3];
	t_vec3	v[3];
	t_vec3	fn;

	idx[0] = obj->out_i[i];
	idx[1] = obj->out_i[i + 1];
	idx[2] = obj->out_i[i + 2];
	v[0] = obj->out_v[idx[0]];
	v[1] = obj->out_v[idx[1]];
	v[2] = obj->out_v[idx[2]];
	fn = vec3_cross(vec3_sub(v[1], v[0]), vec3_sub(v[2], v[0]));
	obj->out_vn[idx[0]] = vec3_add(obj->out_vn[idx[0]], fn);
	obj->out_vn[idx[1]] = vec3_add(obj->out_vn[idx[1]], fn);
	obj->out_vn[idx[2]] = vec3_add(obj->out_vn[idx[2]], fn);
}

static void	accumulate_normals(t_obj *obj)
{
	size_t	i;

	i = 0;
	while (i + 2 < obj->out_i_count)
	{
		add_face_normal(obj, i);
		i += 3;
	}
}

static void	normalize_normals(t_obj *obj)
{
	size_t	i;

	i = 0;
	while (i < obj->out_v_count)
	{
		obj->out_vn[i] = vec3_norm(obj->out_vn[i]);
		i++;
	}
}

void	obj_generate_normals(t_obj *obj)
{
	if (obj->vn_count != 0)
		return ;
	obj->out_vn = ft_calloc(obj->out_v_count, sizeof(t_vec3));
	if (!obj->out_vn)
		return ;
	accumulate_normals(obj);
	normalize_normals(obj);
	obj->vn_count = obj->out_v_count;
}
