/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 16:31:45 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 17:48:30 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glb.h"

/**
 * Iterates through the GLB 'materials' array and parses each material 
 * into the standalone mesh resource system. Returns an array of resource IDs.
 */
t_index	*glb_load_materials(t_mesh_resource *out, void *mlx_ptr,
		t_json_value *json, char *bin)
{
	t_glb_mat		mat;
	size_t			count;
	t_index			*ids;
	t_json_value	*m_array;

	mat.out = out;
	mat.mlx_ptr = mlx_ptr;
	mat.json = json;
	mat.bin = bin;
	m_array = json_get(json, "materials");
	if (!m_array || m_array->type != JSON_ARRAY)
		return (NULL);
	count = m_array->u.array.count;
	ids = malloc(sizeof(t_index) * count);
	if (!ids)
		return (NULL);
	mat.out_ids = ids;
	ft_print_debug("GLB: Parsing %zu material(s)...\n", count);
	mat.mat_idx = 0;
	while (mat.mat_idx < count)
	{
		ft_print_debug("GLB: Material %zu/%zu\n", mat.mat_idx + 1, count);
		ids[mat.mat_idx] = init_index(0, true);
		parse_glb_material(&mat);
		mat.mat_idx++;
	}
	return (ids);
}
