/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getset_soas_ext.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 09:19:10 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/29 09:19:10 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "property.h"

double	get_axis_x(t_scene *scene, int idx)
{
	return ((double)scene->primitives.ax[idx]);
}

void	set_axis_x(t_scene *scene, int idx, double val)
{
	scene->primitives.ax[idx] = (float)val;
	scene_mark_dirty(scene);
}

double	get_axis_y(t_scene *scene, int idx)
{
	return ((double)scene->primitives.ay[idx]);
}

void	set_axis_y(t_scene *scene, int idx, double val)
{
	scene->primitives.ay[idx] = (float)val;
	scene_mark_dirty(scene);
}

double	get_axis_z(t_scene *scene, int idx)
{
	return ((double)scene->primitives.az[idx]);
}

void	set_axis_z(t_scene *scene, int idx, double val)
{
	scene->primitives.az[idx] = (float)val;
	scene_mark_dirty(scene);
}
