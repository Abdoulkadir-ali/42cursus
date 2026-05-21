/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   occlusion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 19:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 17:36:37 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "core.h"

int	scene_occluded(const t_app *app, const t_ray *r, float max_t)
{
	if (bvh_occluded(&app->bvh, r, max_t, app->scene.bvh_objs))
		return (1);
	if (planes_occluded(app->scene.planes, app->scene.n_planes, r, max_t))
		return (1);
	return (0);
}
