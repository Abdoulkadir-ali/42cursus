/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 05:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 05:30:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	snap_light(t_scene_snap *s, t_scene *sc)
{
	snap_array((void **)&s->lights, sc->lights, sc->light_count, sizeof(t_light));
	s->light_count = sc->light_count;
}
