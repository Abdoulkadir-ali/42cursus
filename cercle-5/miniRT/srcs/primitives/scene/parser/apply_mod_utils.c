/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_mod_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 18:22:30 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/09 21:07:21 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

bool	get_last_basic_ref(t_scene *sc, t_type type, t_obj_mat_ref *out)
{
	if (type == TYPE_SPHERE && sc->sphere_count > 0)
	{
		out->mat_id = &sc->spheres[sc->sphere_count - 1].mat_id;
		out->mat_slots = sc->spheres[sc->sphere_count - 1].mat_slots;
		out->active_slot = &sc->spheres[sc->sphere_count - 1].active_slot;
		return (true);
	}
	if (type == TYPE_PLANE && sc->plane_count > 0)
	{
		out->mat_id = &sc->planes[sc->plane_count - 1].mat_id;
		out->mat_slots = sc->planes[sc->plane_count - 1].mat_slots;
		out->active_slot = &sc->planes[sc->plane_count - 1].active_slot;
		return (true);
	}
	if (type == TYPE_CYLINDER && sc->cylinder_count > 0)
	{
		out->mat_id = &sc->cylinders[sc->cylinder_count - 1].mat_id;
		out->mat_slots = sc->cylinders[sc->cylinder_count - 1].mat_slots;
		out->active_slot = &sc->cylinders[sc->cylinder_count - 1].active_slot;
		return (true);
	}
	return (false);
}

bool	get_last_complex_ref(t_scene *sc, t_type type, t_obj_mat_ref *out)
{
	if (type == TYPE_CONE && sc->cone_count > 0)
	{
		out->mat_id = &sc->cones[sc->cone_count - 1].mat_id;
		out->mat_slots = sc->cones[sc->cone_count - 1].mat_slots;
		out->active_slot = &sc->cones[sc->cone_count - 1].active_slot;
		return (true);
	}
	if (type == TYPE_TRI && sc->tri_count > 0)
	{
		out->mat_id = &sc->tris[sc->tri_count - 1].mat_id;
		out->mat_slots = sc->tris[sc->tri_count - 1].mat_slots;
		out->active_slot = &sc->tris[sc->tri_count - 1].active_slot;
		return (true);
	}
	if (type == TYPE_RECT && sc->rect_count > 0)
	{
		out->mat_id = &sc->rects[sc->rect_count - 1].mat_id;
		out->mat_slots = sc->rects[sc->rect_count - 1].mat_slots;
		out->active_slot = &sc->rects[sc->rect_count - 1].active_slot;
		return (true);
	}
	return (false);
}

bool	get_last_vol_ref(t_scene *sc, t_type type, t_obj_mat_ref *out)
{
	if (type == TYPE_PYRAMID && sc->pyramid_count > 0)
	{
		out->mat_id = &sc->pyramids[sc->pyramid_count - 1].mat_id;
		out->mat_slots = sc->pyramids[sc->pyramid_count - 1].mat_slots;
		out->active_slot = &sc->pyramids[sc->pyramid_count - 1].active_slot;
		return (true);
	}
	if (type == TYPE_BOX && sc->box_count > 0)
	{
		out->mat_id = &sc->boxes[sc->box_count - 1].mat_id;
		out->mat_slots = sc->boxes[sc->box_count - 1].mat_slots;
		out->active_slot = &sc->boxes[sc->box_count - 1].active_slot;
		return (true);
	}
	if (type == TYPE_CAPSULE && sc->capsule_count > 0)
	{
		out->mat_id = &sc->capsules[sc->capsule_count - 1].mat_id;
		out->mat_slots = sc->capsules[sc->capsule_count - 1].mat_slots;
		out->active_slot = &sc->capsules[sc->capsule_count - 1].active_slot;
		return (true);
	}
	return (false);
}

static void	apply_prop_sub(t_material *mat, t_mat_mod *mod)
{
	if (mod->kind == MAT_MOD_EMIT_POWER)
	{
		mat->em_intensity = mod->val;
	}
	else if (mod->kind == MAT_MOD_NAME)
	{
		free(mat->name);
		mat->name = ft_strdup(mod->path);
	}
}

void	apply_property(t_material *mat, t_mat_mod *mod)
{
	if (mod->kind == MAT_MOD_ROUGHNESS)
		mat->roughness = mod->val;
	else if (mod->kind == MAT_MOD_METALLIC)
		mat->metallic = mod->val;
	else if (mod->kind == MAT_MOD_EMISSION)
		mat->emission = mod->color_a;
	else if (mod->kind == MAT_MOD_OPACITY)
		mat->transparency = 1.0 - mod->val;
	else if (mod->kind == MAT_MOD_REFLECTIVITY)
		mat->reflectivity = mod->val;
	else if (mod->kind == MAT_MOD_IOR)
		mat->refract_index = mod->val;
	else if (mod->kind == MAT_MOD_SHININESS)
		mat->shininess = mod->val;
	else if (mod->kind == MAT_MOD_UV_SCALE)
		mat->albedo_map.scale = mod->val;
	else
		apply_prop_sub(mat, mod);
}
