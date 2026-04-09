/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attractor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/09 19:10:37 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

bool	scene_add_attractor(t_scene *scene, t_attractor a)
{
	if (!DYNARRAY_ENSURE_INT(&scene->attractors, &scene->attractor_count,
			&scene->attractor_cap, sizeof(t_attractor)))
		return (false);
	scene->attractors[scene->attractor_count++] = a;
	return (true);
}
