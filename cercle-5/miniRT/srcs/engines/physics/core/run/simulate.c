/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 01:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/29 15:15:11 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"
#include "debug.h"
#include <stdlib.h>

void    debug_print_physics_state(t_physics *phys);

void    simulate_physics(t_physics *phys, double dt)
{
        if (phys == NULL)
                return ;
        DBG_INFO_MSG(DBG_CH_PHYSICS, "[simulate_physics]: start p->needs_bake=%d, b_ver=%u, s_ver=%u\n", (int)phys->needs_bake, phys->baked_version, phys->scene->version);
        if (phys->needs_bake || (phys->scene
                        && phys->baked_version != phys->scene->version))
        {
                DBG_INFO_MSG(DBG_CH_PHYSICS, "Physics bake triggered\n");
                phys_bake_scene(phys, phys->scene);
                if (phys->scene)
                        phys->baked_version = phys->scene->version;
                phys->needs_bake = false;
        }
        DBG_TRACE_MSG(DBG_CH_PHYSICS, "Physics step dt=%.4f\n", dt);
        update_physics(phys, dt);
        debug_print_physics_state(phys);
        if (phys->soa && phys->soa->count > 0)
                DBG_INFO_MSG(DBG_CH_PHYSICS, "[simulate_physics]: end pt, v_y=%f\n", phys->soa->hot.vy[0]);
        else
                DBG_INFO_MSG(DBG_CH_PHYSICS, "[simulate_physics]: end pt (no soa)\n");
}

void    physics_destroy(t_physics *phys)
{
        if (phys)
                phys_destroy(phys);
}
