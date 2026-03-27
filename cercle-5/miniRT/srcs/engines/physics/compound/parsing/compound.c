/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compound.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 10:28:11 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/*
** A compound body in the .rt scene is attached to a box as its host shape.
** The host box occupies the scene's boxes array normally, but its phys
** field is replaced with the compound body parsed from the JSON.
** Format:
**  "compound": { "mass":1, "elasticity":0.4, "friction":0.5,
**                "bricks":[{"type":"box","offset":[0,0,0],
**                           "aabb_min":[-1,-1,-1],"aabb_max":[1,1,1]},...] }
*/
static bool	box_has_compound(t_json_value *shape_obj)
{
	t_json_value *c = json_get(shape_obj, "compound");
	return (c && c->type == JSON_OBJECT);
}

static bool	apply_to_box(t_scene *s, t_json_value *shape_obj)
{
	t_physics_body	body;
	t_json_value	*comp;

	comp = json_get(shape_obj, "compound");
	if (!comp)
		return (false);
	body = parse_compound_body(comp);
	if (s->box_count > 0)
		s->boxes[s->box_count - 1].phys = body;
	return (true);
}

/**
 * @brief Post-processes a just-parsed shape JSON object.
 * If the object has a "compound" key, upgrades the last box's phys body.
 * Called by the scene file loader after scene_add_box.
 * Returns false if no compound field present (not an error).
 */
bool	scene_apply_compound(t_scene *scene, t_json_value *shape_obj)
{
	if (!scene || !shape_obj)
		return (false);
	if (!box_has_compound(shape_obj))
		return (false);
	return (apply_to_box(scene, shape_obj));
}
