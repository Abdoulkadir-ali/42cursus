/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 12:51:16 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 13:03:12 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

int	narrow_dispatch_shape_pair(t_physics *phys, t_shape_pair *p, t_contact *c,
		int count, int max)
{
	t_gjk_shape	sa;
	t_gjk_shape	sb;

	(void)count;
	(void)max;
	sa = (t_gjk_shape){phys->scene, p->body_a};
	sb = (t_gjk_shape){phys->scene, p->body_b};
	return (gjk_make_contact(phys, p->body_a, p->body_b, c));
}
