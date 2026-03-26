/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   materials.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/17 00:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

static void	glb_log(const char *fmt, ...)
{
	va_list	args;
	FILE	*f;

	f = fopen("debug_glb.txt", "a");
	if (f)
	{
		va_start(args, fmt);
		vfprintf(f, fmt, args);
		va_end(args);
		fclose(f);
	}
	va_start(args, fmt);
	vfprintf(stderr, fmt, args);
	va_end(args);
}

static void	load_glb_base_texture(t_json_value *json, char *bin,
		t_material *mat, t_json_value *pbr, int mat_idx)
{
	t_json_value	*base_color_tex;
	t_json_value	*textures;
	t_json_value	*t;
	t_json_value	*images;
	t_json_value	*img;
	t_buffer_view	bv;
	int				tex_idx;
	int				source;
	int				bv_idx;

	base_color_tex = json_get(pbr, "baseColorTexture");
	if (!base_color_tex)
		return ;
	tex_idx = json_get_int(base_color_tex, "index");
	textures = json_get(json, "textures");
	t = json_at(textures, tex_idx);
	if (!t)
		return ;
	source = json_get_int(t, "source");
	images = json_get(json, "images");
	img = json_at(images, source);
	if (!img)
		return ;
	bv_idx = json_get_int(img, "bufferView");
	if (bv_idx < 0)
		glb_log("GLB: Material %d base texture has NO bufferView (unsupported uri?)\n", mat_idx);
	glb_parse_buffer_view(json, bv_idx, &bv);
	glb_log("GLB: Material %d texture found at BV %d (offset %d, len %d)\n",
		mat_idx, bv_idx, bv.byte_offset, bv.byte_length);
	if (load_texture_from_memory(&mat->albedo_map,
			(unsigned char *)(bin + bv.byte_offset), bv.byte_length))
		glb_log("GLB: Material %d texture loaded successfully\n", mat_idx);
	else
		glb_log("GLB: Material %d texture LOAD FAILED\n", mat_idx);
}

static void	parse_glb_material(t_scene *scene, t_json_value *json, char *bin,
		int mat_idx, int *out_ids)
{
	t_json_value	*materials;
	t_json_value	*m;
	t_json_value	*pbr;
	t_json_value	*color;
	t_vec3			albedo;
	int				scene_mat_id;
	t_material		*mat;

	materials = json_get(json, "materials");
	m = json_at(materials, mat_idx);
	if (!m || m->type != JSON_OBJECT)
	{
		glb_log("GLB: Material %d is NOT an object (type: %d)\n", mat_idx, m ? (int)m->type : -1);
		return ;
	}
	glb_log("GLB: Investigating Material %d structure...\n", mat_idx);
	scene_mat_id = scene_add_named_material(scene, "glb_material");
	if (scene_mat_id < 0)
		return ;
	out_ids[mat_idx] = scene_mat_id;
	mat = &scene->materials[scene_mat_id];
	albedo = vec3(255, 255, 255);
	
	/* Probing for textures in common locations */
	pbr = json_get(m, "pbrMetallicRoughness");
	if (!pbr)
	{
		glb_log("GLB: Material %d: Standard 'pbrMetallicRoughness' MISSING. Checking fallbacks...\n", mat_idx);
		/* Some GLBs put textures in common-level extensions or just top level (non-spec) */
		load_glb_base_texture(json, bin, &scene->materials[scene_mat_id], m, mat_idx);
	}
	else
	{
		color = json_get(pbr, "baseColorFactor");
		if (color && color->type == JSON_ARRAY && color->array.count >= 3)
		{
			albedo.x = json_as_number(json_at(color, 0)) * 255.0;
			albedo.y = json_as_number(json_at(color, 1)) * 255.0;
			albedo.z = json_as_number(json_at(color, 2)) * 255.0;
			glb_log("GLB: Material %d baseColorFactor: (%.1f, %.1f, %.1f)\n",
				mat_idx, albedo.x, albedo.y, albedo.z);
		}
		scene->materials[scene_mat_id].albedo_map.color_a = albedo;
		load_glb_base_texture(json, bin, &scene->materials[scene_mat_id],
			pbr, mat_idx);
	}
    /* Fallback 2: Check for Unlit/Extensions if still no texture */
    if (!mat->albedo_map.addr)
    {
        t_json_value *ext = json_get(m, "extensions");
        if (ext && ext->type == JSON_OBJECT)
        {
            glb_log("GLB: Material %d has EXTENSIONS. Probing...\n", mat_idx);
            
            /* Probe 1: KHR_materials_pbrSpecularGlossiness */
            t_json_value *sg = json_get(ext, "KHR_materials_pbrSpecularGlossiness");
            if (sg)
            {
                glb_log("GLB: Material %d uses Specular-Glossiness extension\n", mat_idx);
                load_glb_base_texture(json, bin, mat, sg, mat_idx);
                /* SpecGloss uses diffuseTexture instead of baseColorTexture */
                if (!mat->albedo_map.addr)
                {
                    t_json_value *diff = json_get(sg, "diffuseTexture");
                    if (diff)
                    {
                        glb_log("GLB: Found 'diffuseTexture' in SpecGloss extension\n");
                        int tex_idx = json_get_int(diff, "index");
                        /* Use a temporary hack to make load_glb_base_texture work with 'diffuseTexture' */
                        /* Use a temporary hack to make load_glb_base_texture work with 'diffuseTexture' */
                        t_json_value *textures = json_get(json, "textures");
                        t_json_value *t = json_at(textures, tex_idx);
                        if (t) {
                            int source = json_get_int(t, "source");
                            t_json_value *images = json_get(json, "images");
                            t_json_value *img = json_at(images, source);
                            if (img) {
                                int bv_idx = json_get_int(img, "bufferView");
                                if (bv_idx >= 0) {
                                    t_buffer_view bv2;
                                    glb_parse_buffer_view(json, bv_idx, &bv2);
                                    glb_log("GLB: SpecGloss texture found at BV %d (offset %d, len %d)\n", bv_idx, bv2.byte_offset, bv2.byte_length);
                                    if (load_texture_from_memory(&mat->albedo_map, (unsigned char *)(bin + bv2.byte_offset), bv2.byte_length))
                                        glb_log("GLB: SpecGloss texture loaded successfully\n");
                                    else
                                        glb_log("GLB: SpecGloss texture LOAD FAILED\n");
                                } else {
                                    glb_log("GLB: SpecGloss bufferView not found for image source %d\n", source);
                                }
                            } else {
                                glb_log("GLB: SpecGloss image source %d not found\n", source);
                            }
                        } else {
                            glb_log("GLB: SpecGloss texture index %d not found in 'textures' array\n", tex_idx);
                        }
                    }
                }
            }
            
            /* Probe 2: Unlit often just points back to a color, but let's check for weird nesting */
            if (!mat->albedo_map.addr && json_get(ext, "KHR_materials_unlit"))
                glb_log("GLB: Material %d is KHR_materials_unlit\n", mat_idx);
        }
    }
}

int	*glb_load_materials(t_scene *scene, t_json_value *json, char *bin)
{
	t_json_value	*materials;
	int				count;
	int				*ids;
	int				i;

	glb_log("--- GLB: Starting Material Load Stage ---\n");
	materials = json_get(json, "materials");
	if (!materials || materials->type != JSON_ARRAY)
	{
	glb_log("GLB: No 'materials' array found in JSON root\n");
		return (NULL);
	}
	count = (int)materials->array.count;
	glb_log("GLB: Found %d potential materials to process\n", count);
	ids = malloc(sizeof(int) * count);
	if (!ids)
		return (NULL);
	i = 0;
	while (i < count)
	{
		ids[i] = -1;
		parse_glb_material(scene, json, bin, i, ids);
		i++;
	}
	return (ids);
}
