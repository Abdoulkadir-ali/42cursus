/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antigravity <antigravity@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 18:00:00 by antigravity       #+#    #+#             */
/*   Updated: 2026/02/16 18:00:00 by antigravity      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics_internal.h"

/* Global singleton for physics configuration */
static t_physics_state g_phys = {
    .gravity = {0, -9.81, 0, 0},
    .global_damping = 0.5, /* Higher damping for stability */
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
