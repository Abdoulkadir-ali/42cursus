/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sliders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 17:10:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 17:22:35 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void	build_from_props(const t_property **props, t_islider *sl, int *i)
{
	int	j;

	j = 0;
	while (props && props[j])
	{
		sl[*i] = (t_islider){props[j]->name, props[j]->min,
			props[j]->max, NULL, props[j]};
		(*i)++;
		j++;
	}
}

/**
 * @brief Populates the slider array for the transform panel based on object type.
 * @param tr Pointer to the transform structure (legacy).
 * @param type The selected object type.
 * @param sl Output slider array.
 * @param count Output pointer for the number of sliders.
 */
void	build_tr_sliders(t_transform *tr, t_type type, t_islider *sl, int *count)
{
	int	i;

	i = 0;
	(void)tr;
	if (type == TYPE_SPHERE)
		build_from_props(g_props_sphere, sl, &i);
	else if (type == TYPE_PLANE)
		build_from_props(g_props_plane, sl, &i);
	else if (type == TYPE_CYLINDER)
		build_from_props(g_props_cylinder, sl, &i);
	else if (type == TYPE_CONE)
		build_from_props(g_props_cone, sl, &i);
	else if (type == TYPE_CAPSULE)
		build_from_props(g_props_capsule, sl, &i);
	else if (type == TYPE_BOX)
		build_from_props(g_props_box, sl, &i);
	else if (type == TYPE_RECT)
		build_from_props(g_props_rect, sl, &i);
	else if (type == TYPE_PYRAMID)
		build_from_props(g_props_pyramid, sl, &i);
	else if (type == TYPE_MESH)
		build_from_props(g_props_mesh, sl, &i);
	else if (type == TYPE_LIGHT)
		build_from_props(g_props_light, sl, &i);
	*count = i;
}
