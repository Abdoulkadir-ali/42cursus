/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pyramid.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 05:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 05:30:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	reset_pyramid(t_scene *sc, t_scene_snap *s)
{
	sc->pyramid_count = s->pyramid_count;
	ft_memcpy(sc->pyramids, s->pyramids,
		s->pyramid_count * sizeof(t_pyramid));
}
