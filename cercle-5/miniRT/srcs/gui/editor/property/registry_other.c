/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   registry_other.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 09:21:30 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/29 09:21:30 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "property.h"

static const t_property prop_lt_bright = {"Brightness", get_lt_bright, set_lt_bright, 0, 100};
static const t_property prop_lt_r = {"Light R", get_lt_r, set_lt_r, 0, 1};
static const t_property prop_lt_g = {"Light G", get_lt_g, set_lt_g, 0, 1};
static const t_property prop_lt_b = {"Light B", get_lt_b, set_lt_b, 0, 1};
static const t_property prop_lt_px = {"Pos X", get_lt_px, set_lt_px, -1000, 1000};
static const t_property prop_lt_py = {"Pos Y", get_lt_py, set_lt_py, -1000, 1000};
static const t_property prop_lt_pz = {"Pos Z", get_lt_pz, set_lt_pz, -1000, 1000};

static const t_property prop_amb_bright = {"Amb Intensity", get_amb_bright, set_amb_bright, 0, 1};
static const t_property prop_amb_r = {"Amb R", get_amb_r, set_amb_r, 0, 1};
static const t_property prop_amb_g = {"Amb G", get_amb_g, set_amb_g, 0, 1};
static const t_property prop_amb_b = {"Amb B", get_amb_b, set_amb_b, 0, 1};

static const t_property prop_mat_rough = {"Roughness", get_mat_rough, set_mat_rough, 0, 1};
static const t_property prop_mat_metal = {"Metallic", get_mat_metal, set_mat_metal, 0, 1};
static const t_property prop_mat_opac = {"Opacity", get_mat_opac, set_mat_opac, 0, 1};

const t_property *g_props_light[] = {&prop_lt_px, &prop_lt_py, &prop_lt_pz, &prop_lt_r, &prop_lt_g, &prop_lt_b, &prop_lt_bright, NULL};
const t_property *g_props_ambient[] = {&prop_amb_bright, &prop_amb_r, &prop_amb_g, &prop_amb_b, NULL};
const t_property *g_props_material[] = {&prop_mat_rough, &prop_mat_metal, &prop_mat_opac, NULL};
