/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   impulse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 17:22:09 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 17:22:10 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

void	phys_apply_impulse(t_phys_world *w, int obj_idx, t_vec3 impulse)
{
	int		i;
	t_body	*b;

	i = phys_body_for_sphere(w, obj_idx);
	if (i < 0)
		return ;
	b = &w->bodies[i];
	if (b->inv_mass <= 0.0f)
		return ;
	b->vel = v3_add(b->vel, v3_mul(impulse, b->inv_mass));
	b->sleep_frames = 0;
}
