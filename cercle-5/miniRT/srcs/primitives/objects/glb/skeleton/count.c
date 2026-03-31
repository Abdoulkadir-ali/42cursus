/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 16:21:25 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/30 22:29:31 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glb.h"

/**
 * Counts non-joint GLTF nodes that reference a mesh. These need extra bone
 * slots so the rigid transform can follow an animated parent joint.
 */
int	glb_count_extra_anim_nodes(t_json_value *json)
{
	t_json_value	*v[3];
	int				*is_joint;
	int				extra;
	int				nc;
	int				i;

	v[0] = json_get(json_at(json_get(json, "skins"), 0), "joints");
	v[1] = json_get(json, "nodes");
	if (!v[0] || !v[1])
		return (0);
	nc = (int)v[1]->u.array.count;
	is_joint = ft_calloc(65536, sizeof(int));
	if (!is_joint)
		return (0);
	i = -1;
	while (++i < (int)v[0]->u.array.count)
		if ((int)json_as_number(json_at(v[0], i)) < 65536)
			is_joint[(int)json_as_number(json_at(v[0], i))] = 1;
	extra = 0;
	i = -1;
	while (++i < nc && i < 65536)
		if (!is_joint[i] && (int)json_get_int(json_at(v[1], i), "mesh") >= 0)
			extra++;
	free(is_joint);
	return (extra);
}
