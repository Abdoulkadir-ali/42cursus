/* ************************************************************************** */
/*										*/
/*							:::	  ::::::::   */
/*   utils.c						:+:	  :+:	:+:   */
/*							+:+ +:+	 +:+	 */
/*   By: abdoali <abdoali@student.42.fr>		+#+  +:+	   +#+	*/
/*						+#+#+#+#+#+   +#+	   */
/*   Created: 2026/02/12 12:00:00 by abdoali	   #+#	#+#		 */
/*   Updated: 2026/04/03 13:54:14 by abdoali	  ###   ########.fr	   */
/*										*/
/* ************************************************************************** */

#include "obj.h"

static int	obj_fix_index(int idx, size_t count)
{
	if (idx == 0)
		return (-1);
	if (idx < 0)
		return (count + idx);
	return (idx - 1);
}

void	obj_set_out_vertex(t_obj *obj, size_t vi, size_t vti, size_t vni)
{
	if (vi < obj->v_count)
		obj->out_v[obj->out_v_count] = obj->temp_v[vi];
	else
		obj->out_v[obj->out_v_count] = (t_vec3){0, 0, 0, 1.0};
	if (vti < obj->vt_count)
		obj->out_vt[obj->out_v_count] = obj->temp_vt[vti];
	else
		obj->out_vt[obj->out_v_count] = (t_vec2){0, 0};
	if (vni < obj->vn_count)
		obj->out_vn[obj->out_v_count] = obj->temp_vn[vni];
	else
		obj->out_vn[obj->out_v_count] = (t_vec3){0, 1, 0, 0};
}

void	obj_ensure_out_capacity(t_obj *obj)
{
	size_t	cnt;

	cnt = obj->out_v_count;
	if (obj->out_v_count < obj->out_v_cap)
		return ;
	if (!dynarray_ensure((void **)&obj->out_v, cnt,
			&obj->out_v_cap, sizeof(t_vec3))
		|| !dynarray_ensure((void **)&obj->out_vt, cnt,
			&obj->out_v_cap, sizeof(t_vec2))
		|| !dynarray_ensure((void **)&obj->out_vn, cnt,
			&obj->out_v_cap, sizeof(t_vec3)))
		return ;
}

void	obj_add_vert(t_obj *obj, int vi, int vti, int vni)
{
	int	v_idx;
	int	vt_idx;
	int	vn_idx;

	obj_ensure_out_capacity(obj);
	v_idx = obj_fix_index(vi, obj->v_count);
	vt_idx = obj_fix_index(vti, obj->vt_count);
	vn_idx = obj_fix_index(vni, obj->vn_count);
	obj_set_out_vertex(obj, v_idx, vt_idx, vn_idx);
	if (!dynarray_ensure((void **)&obj->out_i, obj->out_i_count,
			&obj->out_i_cap, sizeof(size_t)))
		return ;
	obj->out_i[obj->out_i_count++] = obj->out_v_count++;
}
