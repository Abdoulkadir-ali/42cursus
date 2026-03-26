/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sliders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 17:10:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 08:41:58 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void	build_complex_tr(t_transform *tr, t_type type, t_islider *sl, int *i)
{
	if (type == TYPE_MESH || type == TYPE_BOX)
	{
		sl[(*i)++] = (t_islider){"Scale X", SL_SCALE_MIN, SL_SCALE_MAX, &tr->scale.x};
		sl[(*i)++] = (t_islider){"Scale Y", SL_SCALE_MIN, SL_SCALE_MAX, &tr->scale.y};
		sl[(*i)++] = (t_islider){"Scale Z", SL_SCALE_MIN, SL_SCALE_MAX, &tr->scale.z};
	}
	else if (type == TYPE_CAPSULE)
	{
		sl[(*i)++] = (t_islider){"Radius", SL_SCALE_MIN, SL_SCALE_MAX, &tr->scale.x};
		sl[(*i)++] = (t_islider){"Half-H", SL_SCALE_MIN, SL_SCALE_MAX, &tr->scale.y};
	}
	else if (type == TYPE_PLANE)
		sl[(*i)++] = (t_islider){"UV Scale", SL_SCALE_MIN, SL_SCALE_MAX, &tr->scale.x};
}

/**
 * @brief Populates the slider array for the transform panel based on object type.
 * @param tr Pointer to the transform structure.
 * @param type The selected object type.
 * @param sl Output slider array.
 * @param count Output pointer for the number of sliders.
 */
void	build_tr_sliders(t_transform *tr, t_type type, t_islider *sl, int *count)
{
	int	i;

	i = 0;
	sl[i++] = (t_islider){"Pos X", SL_POS_MIN, SL_POS_MAX, &tr->pos.x};
	sl[i++] = (t_islider){"Pos Y", SL_POS_MIN, SL_POS_MAX, &tr->pos.y};
	sl[i++] = (t_islider){"Pos Z", SL_POS_MIN, SL_POS_MAX, &tr->pos.z};
	sl[i++] = (t_islider){"Pitch", SL_ROT_MIN, SL_ROT_MAX, &tr->rotation.pitch};
	sl[i++] = (t_islider){"Yaw", SL_ROT_MIN, SL_ROT_MAX, &tr->rotation.yaw};
	sl[i++] = (t_islider){"Roll", SL_ROT_MIN, SL_ROT_MAX, &tr->rotation.roll};
	if (type == TYPE_SPHERE)
		sl[i++] = (t_islider){"Scale", SL_SCALE_MIN, SL_SCALE_MAX, &tr->scale.x};
	else if (type == TYPE_CYLINDER || type == TYPE_CONE)
	{
		sl[i++] = (t_islider){"Radius", SL_SCALE_MIN, SL_SCALE_MAX, &tr->scale.x};
		sl[i++] = (t_islider){"Height", SL_SCALE_MIN, SL_SCALE_MAX, &tr->scale.y};
	}
	else
		build_complex_tr(tr, type, sl, &i);
	*count = i;
}
