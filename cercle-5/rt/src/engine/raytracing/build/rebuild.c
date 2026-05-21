/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rebuild.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 18:47:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 00:29:11 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"
#include "core.h"

int	bvh_rebuild(t_app *app)
{
	bvh_free(&app->bvh);
	if (bvh_build(&app->bvh, app->scene.bvh_objs, app->scene.n_bvh) < 0)
		return (-1);
	bvh_prepare_simd(&app->bvh, app->scene.bvh_objs);
	return (0);
}
