/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 04:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 03:27:18 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skeletal.h"

void	skel_animator_apply_extra_xform(t_animator *a, const t_mat4 m)
{
	if (!a)
		return ;
	memcpy(a->extra, m, sizeof(float) * 16);
	a->has_extra = 1;
}
