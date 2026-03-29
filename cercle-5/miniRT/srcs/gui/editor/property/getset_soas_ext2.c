/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getset_soas_ext2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 09:19:20 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/29 09:19:20 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "property.h"

double	get_ext_x(t_scene *scene, int idx)
{
	return ((double)scene->primitives.ex[idx]);
}

void	set_ext_x(t_scene *scene, int idx, double val)
{
	scene->primitives.ex[idx] = (float)val;
	scene_mark_dirty(scene);
}

double	get_ext_y(t_scene *scene, int idx)
{
	return ((double)scene->primitives.ey[idx]);
}

void	set_ext_y(t_scene *scene, int idx, double val)
{
	scene->primitives.ey[idx] = (float)val;
	scene_mark_dirty(scene);
}

double	get_ext_z(t_scene *scene, int idx)
{
	return ((double)scene->primitives.ez[idx]);
}

void	set_ext_z(t_scene *scene, int idx, double val)
{
	scene->primitives.ez[idx] = (float)val;
	scene_mark_dirty(scene);
}
