/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solids.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 17:22:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 08:41:58 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	delete_sel_solids(t_scene *sc, t_selection *sel)
{
	int	i;

	i = sel->index;
	if (sel->type == TYPE_CYLINDER && i < sc->cylinder_count)
	{
		ft_memmove(sc->cylinders + i, sc->cylinders + i + 1, (sc->cylinder_count
				- i - 1) * sizeof(t_cylinder));
		sc->cylinder_count--;
		return ;
	}
	if (sel->type == TYPE_CONE && i < sc->cone_count)
	{
		ft_memmove(sc->cones + i, sc->cones + i + 1, (sc->cone_count - i - 1)
			* sizeof(t_cone));
		sc->cone_count--;
		return ;
	}
	if (sel->type == TYPE_TRI && i < sc->tri_count)
	{
		ft_memmove(sc->tris + i, sc->tris + i + 1, (sc->tri_count - i - 1)
			* sizeof(t_tri_shape));
		sc->tri_count--;
		return ;
	}
}
