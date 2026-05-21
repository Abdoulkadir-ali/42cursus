/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   query.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 04:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 03:27:18 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skeletal.h"

int	skel_animator_clip_count(const t_animator *a)
{
	if (!a)
		return (0);
	return (a->n_clips);
}

const char	*skel_animator_clip_name(const t_animator *a, int i)
{
	if (!a || i < 0 || i >= a->n_clips)
		return ("");
	return (a->clips[i].name);
}

float	skel_animator_clip_duration(const t_animator *a, int i)
{
	if (!a || i < 0 || i >= a->n_clips)
		return (0.0f);
	return (a->clips[i].duration);
}
