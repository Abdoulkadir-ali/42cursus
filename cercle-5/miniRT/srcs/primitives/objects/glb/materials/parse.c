/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 16:35:55 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 14:23:13 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glb.h"

static void	parse_pbr(t_glb_mat *mat, size_t s_id, t_json_value *m)
{
	t_json_value	*pbr;
	t_json_value	*color;
	t_vec3			albedo;

	pbr = json_get(m, "pbrMetallicRoughness");
	albedo = vec3(255, 255, 255);
	if (!pbr)
		load_glb_base_texture(mat->json, mat->bin, &mat->out->materials[s_id],
			m);
	else
	{
		color = json_get(pbr, "baseColorFactor");
		if (color && color->type == JSON_ARRAY && color->u.array.count >= 3)
		{
			albedo.x = json_as_number(json_at(color, 0)) * 255.0;
			albedo.y = json_as_number(json_at(color, 1)) * 255.0;
			albedo.z = json_as_number(json_at(color, 2)) * 255.0;
		}
		mat->out->materials[s_id].albedo_map.color_a = albedo;
		load_glb_base_texture(mat->json, mat->bin, &mat->out->materials[s_id],
			pbr);
	}
}

static void	parse_specgloss(t_glb_mat *mat, size_t s_id, t_json_value *ext)
{
	t_json_value	*sg;

	sg = json_get(ext, "KHR_materials_pbrSpecularGlossiness");
	if (sg)
	{
		glb_log("GLB: Material uses Specular-Glossiness extension\n");
		load_glb_base_texture(mat->json, mat->bin, &mat->out->materials[s_id],
			sg);
	}
}

/**
 * Parses an individual GLB material definition from the JSON.
 */
void	parse_glb_material(t_glb_mat *mat)
{
	t_json_value	*m;
	t_json_value	*ext;
	size_t			s_id;
	bool			err;

	m = json_at(json_get(mat->json, "materials"), mat->mat_idx);
	if (!m || m->type != JSON_OBJECT)
		return ;
	s_id = mesh_resource_add_material(mat->out, "glb_material", &err);
	if (err)
		return ;
	mat->out_ids[mat->mat_idx] = init_index(s_id, false);
	parse_pbr(mat, s_id, m);
	if (!mat->out->materials[s_id].albedo_map.addr)
	{
		ext = json_get(m, "extensions");
		if (ext && ext->type == JSON_OBJECT)
			parse_specgloss(mat, s_id, ext);
	}
}
