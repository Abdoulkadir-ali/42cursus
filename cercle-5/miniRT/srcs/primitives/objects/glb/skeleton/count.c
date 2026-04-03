/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 16:21:25 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 14:12:43 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glb.h"

static void	mark_joints(t_json_value *joints, size_t *is_joint)
{
	size_t	i;
	size_t	idx;

	i = 0;
	while (i < joints->u.array.count)
	{
		idx = json_as_number(json_at(joints, i));
		if (idx < PARSER_BUF_SIZE)
			is_joint[idx] = 1;
		i++;
	}
}

static int	count_extra(t_json_value *nodes, size_t *is_joint, size_t nc)
{
	int		extra;
	size_t	i;

	extra = 0;
	i = 0;
	while (i < nc && i < PARSER_BUF_SIZE)
	{
		if (!is_joint[i] && !json_get_size_t(json_at(nodes, i), "mesh").error)
			extra++;
		i++;
	}
	return (extra);
}

/**
 * Counts non-joint GLTF nodes that reference a mesh. These need extra bone
 * slots so the rigid transform can follow an animated parent joint.
 */
int	glb_count_extra_anim_nodes(t_json_value *json)
{
	t_json_value	*v[2];
	size_t			*is_joint;
	int				extra;

	v[0] = json_get(json_at(json_get(json, "skins"), 0), "joints");
	v[1] = json_get(json, "nodes");
	if (!v[0] || !v[1])
		return (0);
	is_joint = ft_calloc(PARSER_BUF_SIZE, sizeof(size_t));
	if (!is_joint)
		return (0);
	mark_joints(v[0], is_joint);
	extra = count_extra(v[1], is_joint, v[1]->u.array.count);
	free(is_joint);
	return (extra);
}
