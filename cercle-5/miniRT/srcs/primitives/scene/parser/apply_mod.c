/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_mod.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 19:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/08 18:48:57 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

static bool	get_last_obj_ref(t_scene *sc, t_type type, t_obj_mat_ref *out)
{
	if (get_last_basic_ref(sc, type, out))
		return (true);
	if (get_last_complex_ref(sc, type, out))
		return (true);
	if (get_last_vol_ref(sc, type, out))
		return (true);
	if (type == TYPE_MESH && sc->mesh_count > 0)
	{
		out->mat_id = &sc->meshes[sc->mesh_count - 1].mat_id;
		out->mat_slots = sc->meshes[sc->mesh_count - 1].mat_slots;
		out->active_slot = &sc->meshes[sc->mesh_count - 1].active_slot;
		return (true);
	}
	if (type == TYPE_ANIM && sc->anim_count > 0)
	{
		out->mat_id = &sc->animated[sc->anim_count - 1].base.mat_id;
		out->mat_slots = sc->animated[sc->anim_count - 1].base.mat_slots;
		out->active_slot = &sc->animated[sc->anim_count - 1].base.active_slot;
		return (true);
	}
	return (false);
}

static size_t	ensure_private_mat(t_scene *sc, t_obj_mat_ref *ref,
		bool *cloned)
{
	t_index	cl;
	size_t	cur;

	cur = ref->mat_slots[*ref->active_slot];
	if (*cloned)
		return (cur);
	cl = scene_clone_material(sc, cur);
	if (cl.error)
		return (cur);
	ref->mat_slots[*ref->active_slot] = cl.i;
	*ref->mat_id = cl.i;
	*cloned = true;
	return (cl.i);
}

static void	apply_mat_type_res(t_scene *sc, t_obj_mat_ref *ref,
		t_mat_mod *mod, size_t id)
{
	if (mod->kind == MAT_MOD_TEXTURE && mod->path[0] != '\0' && sc->mlx)
		load_texture(sc->mlx, &sc->materials[id].albedo_map, mod->path);
	if (mod->kind == MAT_MOD_TEXTURE)
	{
		ref->mat_slots[3] = id;
		*ref->active_slot = 3;
	}
	else
	{
		ref->mat_slots[0] = id;
		*ref->active_slot = 0;
	}
	*ref->mat_id = id;
}

static void	apply_mat_type(t_scene *sc, t_obj_mat_ref *ref,
		t_mat_mod *mod, bool *cloned)
{
	t_index	id;

	if (mod->kind == MAT_MOD_SOLID || mod->kind == MAT_MOD_TEXTURE)
	{
		if (mod->kind == MAT_MOD_SOLID)
			id = scene_add_fresh_material(sc, mod->color_a);
		else
			id = scene_add_fresh_material(sc, vec3(255, 255, 255));
		if (!id.error)
		{
			apply_mat_type_res(sc, ref, mod, id.i);
			*cloned = true;
		}
	}
	else if (mod->kind == MAT_MOD_CHECKER)
	{
		id.i = scene_add_checker_material(sc, mod->color_a, mod->color_b,
				(double)(mod->scale > 0.0) * mod->scale
				+ (double)(mod->scale <= 0.0));
		ref->mat_slots[1] = id.i;
		*ref->mat_id = id.i;
		*ref->active_slot = 1;
		*cloned = true;
	}
}

void	apply_mat_mod_to_last(t_scene *scene, t_rt *rt, t_mat_mod *mod)
{
	t_obj_mat_ref	ref;
	size_t			mat_id;

	if (rt->last_type == TYPE_NONE)
		return ;
	if (mod->kind >= MAT_MOD_PHYS_MASS && mod->kind <= MAT_MOD_PHYS_FRIC)
	{
		apply_phys_mod(scene, mod, rt->last_type);
		return ;
	}
	if (!get_last_obj_ref(scene, rt->last_type, &ref))
		return ;
	if (mod->kind >= MAT_MOD_SOLID && mod->kind <= MAT_MOD_TEXTURE)
	{
		apply_mat_type(scene, &ref, mod, &rt->last_mat_cloned);
		return ;
	}
	if (mod->kind == MAT_MOD_BUMP && scene->mlx)
	{
		mat_id = ensure_private_mat(scene, &ref, &rt->last_mat_cloned);
		load_texture(scene->mlx, &scene->materials[mat_id].bump_map, mod->path);
		return ;
	}
	mat_id = ensure_private_mat(scene, &ref, &rt->last_mat_cloned);
	apply_property(&scene->materials[mat_id], mod);
}
