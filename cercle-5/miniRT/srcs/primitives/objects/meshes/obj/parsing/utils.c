/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   faces_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/12 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "obj.h"

int	obj_fix_index(int idx, int count)
{
	if (idx == 0)
		return (-1);
	if (idx < 0)
		return (count + idx);
	return (idx - 1);
}

void	obj_set_out_vertex(t_obj *obj, int vi, int vti, int vni)
{
	if (vi >= 0 && vi < (int)obj->v_count)
		obj->out_v[obj->out_v_count] = obj->temp_v[vi];
	else
		obj->out_v[obj->out_v_count] = (t_vec3){0, 0, 0, 1.0};
	if (vti >= 0 && vti < (int)obj->vt_count)
		obj->out_vt[obj->out_v_count] = obj->temp_vt[vti];
	else
		obj->out_vt[obj->out_v_count] = (t_vec2){0, 0};
	if (vni >= 0 && vni < (int)obj->vn_count)
		obj->out_vn[obj->out_v_count] = obj->temp_vn[vni];
	else
		obj->out_vn[obj->out_v_count] = (t_vec3){0, 1, 0, 0};
}

void	obj_ensure_out_capacity(t_obj *obj)
{
	size_t	cap;

	if (obj->out_v_count < obj->out_v_cap)
		return ;
	cap = obj->out_v_cap;
	if (!dynarray_ensure((void **)&obj->out_v, obj->out_v_count, &cap,
			sizeof(t_vec3)))
		return ;
	cap = obj->out_v_cap;
	if (!dynarray_ensure((void **)&obj->out_vt, obj->out_v_count, &cap,
			sizeof(t_vec2)))
		return ;
	cap = obj->out_v_cap;
	if (!dynarray_ensure((void **)&obj->out_vn, obj->out_v_count, &cap,
			sizeof(t_vec3)))
		return ;
	obj->out_v_cap = cap;
}

void	obj_add_vert(t_obj *obj, int vi, int vti, int vni)
{
	obj_ensure_out_capacity(obj);
	vi = obj_fix_index(vi, (int)obj->v_count);
	vti = obj_fix_index(vti, (int)obj->vt_count);
	vni = obj_fix_index(vni, (int)obj->vn_count);
	obj_set_out_vertex(obj, vi, vti, vni);
	if (!dynarray_ensure((void **)&obj->out_i, obj->out_i_count,
			&obj->out_i_cap, sizeof(int)))
		return ;
	obj->out_i[obj->out_i_count++] = obj->out_v_count++;
}
