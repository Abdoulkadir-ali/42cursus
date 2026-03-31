/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 16:21:15 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/30 22:29:31 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glb.h"

/**
 * Parses and fills a bone's TRS (Translation, Rotation, Scale) properties 
 * from a JSON node.
 */
static void	parse_trs_props(t_json_value *node, t_vec3 *t,
				t_vec4 *r, double s[3])
{
	t_json_value	*v[3];

	v[0] = json_get(node, "translation");
	if (v[0])
		*t = vec3(json_as_number(json_at(v[0], 0)),
				json_as_number(json_at(v[0], 1)),
				json_as_number(json_at(v[0], 2)));
	v[1] = json_get(node, "rotation");
	if (v[1])
		*r = (t_vec4){json_as_number(json_at(v[1], 0)),
			json_as_number(json_at(v[1], 1)), json_as_number(json_at(v[1], 2)),
			json_as_number(json_at(v[1], 3))};
	v[2] = json_get(node, "scale");
	if (v[2])
	{
		s[0] = json_as_number(json_at(v[2], 0));
		s[1] = json_as_number(json_at(v[2], 1));
		s[2] = json_as_number(json_at(v[2], 2));
	}
}

void	fill_bone_trs(t_bone *bone, t_json_value *node)
{
	t_vec3	t;
	t_vec4	r;
	double	s[3];

	t = vec3(0, 0, 0);
	r = (t_vec4){0, 0, 0, 1};
	s[0] = 1;
	s[1] = 1;
	s[2] = 1;
	parse_trs_props(node, &t, &r, s);
	bone->trs.pos = t;
	bone->trs.rot = vec3(r.x, r.y, r.z);
	bone->trs.scale = vec3(s[0], s[1], s[2]);
	bone->local_transform = make_transform(t, r, s);
	bone->global_transform = bone->local_transform;
	bone->inv_bind_pose = mat4_identity();
	bone->bind_pose = bone->local_transform;
}
