/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   registry_mesh_phys.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 09:21:40 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/29 09:21:40 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "property.h"

static const t_property prop_mesh_sx = {"Scale X", get_mesh_sx, set_mesh_sx, 0.1, 10};
static const t_property prop_mesh_sy = {"Scale Y", get_mesh_sy, set_mesh_sy, 0.1, 10};
static const t_property prop_mesh_sz = {"Scale Z", get_mesh_sz, set_mesh_sz, 0.1, 10};
static const t_property prop_mesh_px = {"Pos X", get_mesh_px, set_mesh_px, -1000, 1000};
static const t_property prop_mesh_py = {"Pos Y", get_mesh_py, set_mesh_py, -1000, 1000};
static const t_property prop_mesh_pz = {"Pos Z", get_mesh_pz, set_mesh_pz, -1000, 1000};

static const t_property prop_ph_mass = {"Mass (kg)", get_ph_mass, set_ph_mass, 0.01, 1000};
static const t_property prop_ph_elast = {"Elasticity", get_ph_elast, set_ph_elast, 0, 1.2};
static const t_property prop_ph_fric = {"Friction", get_ph_fric, set_ph_fric, 0, 1};

const t_property *g_props_mesh[] = {&prop_mesh_px, &prop_mesh_py, &prop_mesh_pz, &prop_mesh_sx, &prop_mesh_sy, &prop_mesh_sz, NULL};
const t_property *g_props_physics[] = {&prop_ph_mass, &prop_ph_elast, &prop_ph_fric, NULL};
