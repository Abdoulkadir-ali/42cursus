/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_mod.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 19:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/13 14:05:22 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

static void	apply_mat_type(t_scene *sc, t_obj_mat_ref *ref,
		t_mat_mod *mod, bool *cloned)
{
	t_index	id;
	int		tex;

	if (mod->kind == MAT_MOD_SOLID || mod->kind == MAT_MOD_TEXTURE)
	{
		tex = (mod->kind == MAT_MOD_TEXTURE);
		id = scene_add_fresh_material(sc, mod->color_a);
		if (tex)
			sc->materials[id.i].albedo_map.color_a = vec3(255, 255, 255);
		if (!id.error && tex && mod->path[0] && sc->mlx)
			load_texture(sc->mlx, &sc->materials[id.i].albedo_map, mod->path);
		ref->mat_slots[3 * tex] = id.i;
		*ref->active_slot = 3 * tex;
		*ref->mat_id = id.i;
	}
	else if (mod->kind == MAT_MOD_CHECKER)
	{
		id.i = scene_add_checker_material(sc, mod->color_a, mod->color_b,
				(double)(mod->scale > 0.0) * mod->scale + (mod->scale <= 0.0));
		ref->mat_slots[1] = id.i;
		*ref->mat_id = id.i;
		*ref->active_slot = 1;
	}
	*cloned = true;
}

static void	apply_scene_mod_phys(t_scene *sc, t_mat_mod *mod, t_type last)
{
	if (mod->kind == MAT_MOD_SCENE_WIND)
	{
		sc->scene_wind = mod->color_a;
		sc->scene_wind_set = true;
	}
	else if (mod->kind == MAT_MOD_SCENE_TURBULENCE)
	{
		sc->scene_turbulence = mod->val;
		sc->scene_turbulence_set = true;
	}
	else if (mod->kind >= MAT_MOD_PHYS_MASS
		&& mod->kind <= MAT_MOD_PHYS_MAGNETIC)
		apply_phys_mod(sc, mod, last);
}

static void	apply_scene_mod(t_scene *sc, t_mat_mod *mod, t_type last)
{
	if (mod->kind == MAT_MOD_SCENE_GRAVITY)
	{
		sc->scene_gravity = mod->color_a;
		sc->scene_gravity_set = true;
	}
	else if (mod->kind == MAT_MOD_SCENE_BIG_G)
	{
		sc->scene_big_g = mod->val;
		sc->scene_big_g_set = true;
	}
	else if (mod->kind == MAT_MOD_SCENE_DAMP)
	{
		sc->scene_damping = mod->val;
		sc->scene_damping_set = true;
	}
	else
		apply_scene_mod_phys(sc, mod, last);
}

void	apply_mat_mod_to_last(t_scene *scene, t_rt *rt, t_mat_mod *mod)
{
	t_obj_mat_ref	ref;
	size_t			id;

	if (rt->last_type == TYPE_NONE || (mod->kind >= MAT_MOD_SCENE_GRAVITY
			&& mod->kind <= MAT_MOD_PHYS_MAGNETIC))
		return (apply_scene_mod(scene, mod, rt->last_type));
	if (!get_last_obj_ref(scene, rt->last_type, &ref))
		return ;
	if (mod->kind >= MAT_MOD_SOLID && mod->kind <= MAT_MOD_TEXTURE)
		return (apply_mat_type(scene, &ref, mod, &rt->last_mat_cloned));
	if (!rt->last_mat_cloned)
	{
		id = scene_clone_material(scene, ref.mat_slots[*ref.active_slot]).i;
		ref.mat_slots[*ref.active_slot] = id;
		*ref.mat_id = id;
		rt->last_mat_cloned = true;
	}
	id = *ref.mat_id;
	if (mod->kind == MAT_MOD_BUMP && scene->mlx)
		load_texture(scene->mlx, &scene->materials[id].bump_map, mod->path);
	else
		apply_property(&scene->materials[id], mod);
}
