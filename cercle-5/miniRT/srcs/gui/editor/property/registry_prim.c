/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   registry_prim.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 09:21:20 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/29 09:25:48 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "property.h"

static const t_property prop_pos_x = {"Position X", get_pos_x, set_pos_x, -1000, 1000};
static const t_property prop_pos_y = {"Position Y", get_pos_y, set_pos_y, -1000, 1000};
static const t_property prop_pos_z = {"Position Z", get_pos_z, set_pos_z, -1000, 1000};
static const t_property prop_axis_x = {"Axis X", get_axis_x, set_axis_x, -1, 1};
static const t_property prop_axis_y = {"Axis Y", get_axis_y, set_axis_y, -1, 1};
static const t_property prop_axis_z = {"Axis Z", get_axis_z, set_axis_z, -1, 1};
static const t_property prop_ext_x = {"Ext X", get_ext_x, set_ext_x, 0.01, 100};
static const t_property prop_ext_y = {"Ext Y", get_ext_y, set_ext_y, 0.01, 100};
static const t_property prop_ext_z = {"Ext Z", get_ext_z, set_ext_z, 0.01, 100};
static const t_property prop_radius = {"Radius", get_radius, set_radius, 0.01, 100};
static const t_property prop_height = {"Height", get_height, set_height, 0.01, 100};

const t_property *g_props_sphere[] = {&prop_pos_x, &prop_pos_y, &prop_pos_z, &prop_radius, NULL};
const t_property *g_props_plane[] = {&prop_pos_x, &prop_pos_y, &prop_pos_z, &prop_axis_x, &prop_axis_y, &prop_axis_z, NULL};
const t_property *g_props_cylinder[] = {&prop_pos_x, &prop_pos_y, &prop_pos_z, &prop_axis_x, &prop_axis_y, &prop_axis_z, &prop_radius, &prop_height, NULL};
const t_property *g_props_cone[] = {&prop_pos_x, &prop_pos_y, &prop_pos_z, &prop_axis_x, &prop_axis_y, &prop_axis_z, &prop_radius, &prop_height, NULL};
const t_property *g_props_capsule[] = {&prop_pos_x, &prop_pos_y, &prop_pos_z, &prop_axis_x, &prop_axis_y, &prop_axis_z, &prop_radius, &prop_height, NULL};
const t_property *g_props_box[] = {&prop_pos_x, &prop_pos_y, &prop_pos_z, &prop_ext_x, &prop_ext_y, &prop_ext_z, NULL};
const t_property *g_props_rect[] = {&prop_pos_x, &prop_pos_y, &prop_pos_z, &prop_axis_x, &prop_axis_y, &prop_axis_z, &prop_ext_x, &prop_ext_y, NULL};
const t_property *g_props_pyramid[] = {&prop_pos_x, &prop_pos_y, &prop_pos_z, &prop_axis_x, &prop_axis_y, &prop_axis_z, &prop_ext_x, &prop_ext_y, &prop_height, NULL};
