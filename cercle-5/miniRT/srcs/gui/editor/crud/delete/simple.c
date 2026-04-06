/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 13:41:46 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	delete_sel_sp_pl(t_scene *sc, t_selection *sel)
{
	size_t	i;

	i = sel->index.i;
	if (sel->type == TYPE_SPHERE && i < sc->sphere_count)
	{
		ft_memmove(sc->spheres + i, sc->spheres + i + 1,
			(sc->sphere_count - i - 1) * sizeof(t_sphere));
		sc->sphere_count--;
	}
	else if (sel->type == TYPE_PLANE && i < sc->plane_count)
	{
		ft_memmove(sc->planes + i, sc->planes + i + 1,
			(sc->plane_count - i - 1) * sizeof(t_plane));
		sc->plane_count--;
	}
}
