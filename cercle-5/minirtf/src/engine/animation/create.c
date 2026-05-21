/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 04:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 03:26:18 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skeletal.h"

t_animator	*skel_animator_create(void)
{
	t_animator	*a;

	a = (t_animator *)calloc(1, sizeof(t_animator));
	if (!a)
		return (NULL);
	a->active = -1;
	a->speed = 1.0f;
	a->loop = 1;
	a->playing = 0;
	a->pre_scale = 1.0f;
	a->pre[0] = 1.0f;
	a->pre[4] = 1.0f;
	a->pre[8] = 1.0f;
	return (a);
}
