/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getset_soas_rh.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 09:19:30 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/29 09:19:30 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "property.h"

double	get_radius(t_scene *scene, int idx)
{
	return ((double)scene->primitives.radii[idx]);
}

void	set_radius(t_scene *scene, int idx, double val)
{
	scene->primitives.radii[idx] = (float)val;
	scene_mark_dirty(scene);
}

double	get_height(t_scene *scene, int idx)
{
	return ((double)scene->primitives.heights[idx]);
}

void	set_height(t_scene *scene, int idx, double val)
{
	scene->primitives.heights[idx] = (float)val;
	scene_mark_dirty(scene);
}
