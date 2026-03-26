/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prims.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 17:21:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/25 16:15:06 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	delete_sel_prims(t_scene *sc, t_selection *sel)
{
	int	i;

	i = sel->index;
	if (sel->type == TYPE_SPHERE && i < sc->sphere_count)
	{
		ft_memmove(sc->spheres + i, sc->spheres + i + 1, (sc->sphere_count - i
				- 1) * sizeof(t_sphere));
		sc->sphere_count--;
		return ;
	}
	if (sel->type == TYPE_PLANE && i < sc->plane_count)
	{
		ft_memmove(sc->planes + i, sc->planes + i + 1, (sc->plane_count - i - 1)
			* sizeof(t_plane));
		sc->plane_count--;
		return ;
	}
}
