/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_last_ref.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 05:20:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/12 05:20:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

bool	get_last_obj_ref(t_scene *sc, t_type type, t_obj_mat_ref *out)
{
	if (get_last_basic_ref(sc, type, out))
		return (true);
	if (get_last_complex_ref(sc, type, out))
		return (true);
	if (get_last_vol_ref(sc, type, out))
		return (true);
	if ((type == TYPE_MESH || type == TYPE_SOFT_BODY) && sc->mesh_count > 0)
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
