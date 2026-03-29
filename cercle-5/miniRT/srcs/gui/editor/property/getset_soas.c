/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getset_soas.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 09:19:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/29 09:19:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "property.h"

double	get_pos_x(t_scene *scene, int idx)
{
	return ((double)scene->primitives.px[idx]);
}

void	set_pos_x(t_scene *scene, int idx, double val)
{
	scene->primitives.px[idx] = (float)val;
	scene_mark_dirty(scene);
}

double	get_pos_y(t_scene *scene, int idx)
{
	return ((double)scene->primitives.py[idx]);
}

void	set_pos_y(t_scene *scene, int idx, double val)
{
	scene->primitives.py[idx] = (float)val;
	scene_mark_dirty(scene);
}

double	get_pos_z(t_scene *scene, int idx)
{
	return ((double)scene->primitives.pz[idx]);
}

void	set_pos_z(t_scene *scene, int idx, double val)
{
	scene->primitives.pz[idx] = (float)val;
	scene_mark_dirty(scene);
}
