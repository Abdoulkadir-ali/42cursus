/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   targets.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 19:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 17:49:13 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "props_internal.h"

int	last_targets(t_scene *s, t_object **arr_out)
{
	if (s->last_kind == 1)
	{
		*arr_out = s->bvh_objs + s->last_first;
		return (s->last_count);
	}
	if (s->last_kind == 2)
	{
		*arr_out = s->planes + s->last_first;
		return (s->last_count);
	}
	*arr_out = NULL;
	return (0);
}
