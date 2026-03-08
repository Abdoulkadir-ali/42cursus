/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 20:31:31 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/06 20:31:31 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "physics.h"

/* Global singleton for physics configuration */
static t_physics_state g_phys = {
    .gravity = {0, -9.81, 0, 0},
    .global_damping = 0.12, /* Light air resistance */
    .time_scale = 1.0,
	.mesh_simplify_collision = 1
};

t_physics_state *get_physics_state(void)
{
    return (&g_phys);
}

double clamp_d(double v, double lo, double hi)
{
    if (v < lo)
        return (lo);
    if (v > hi)
        return (hi);
    return (v);
}
