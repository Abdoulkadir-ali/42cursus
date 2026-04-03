/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 16:31:45 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/30 22:29:31 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glb.h"

/**
 * Iterates through the GLB 'materials' array and parses each material 
 * into the standalone mesh resource system. Returns an array of resource IDs.
 */
int	*glb_load_materials(t_mesh_resource *out, void *mlx_ptr,
		t_json_value *json, char *bin)
{
	t_glb_mat		mat;
	int				count;
	int				*ids;
	t_json_value	*m_array;

	mat.out = out;
	mat.mlx_ptr = mlx_ptr;
	mat.json = json;
	mat.bin = bin;
	m_array = json_get(json, "materials");
	if (!m_array || m_array->type != JSON_ARRAY)
		return (NULL);
	count = m_array->u.array.count;
	ids = malloc(sizeof(size_t) * count);
	if (!ids)
		return (NULL);
	mat.out_ids = ids;
	mat.mat_idx = -1;
	while (++mat.mat_idx < count)
	{
		ids[mat.mat_idx] = -1;
		parse_glb_material(&mat);
	}
	return (ids);
}
