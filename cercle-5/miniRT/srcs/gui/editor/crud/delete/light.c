/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 17:20:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/25 16:09:20 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

bool	handle_delete_light(t_scene *sc, t_selection *sel, int i)
{
	if (sel->type != TYPE_LIGHT || i >= sc->light_count)
		return (false);
	ft_memmove(sc->lights + i, sc->lights + i + 1,
		(sc->light_count - i - 1) * sizeof(t_light));
	sc->light_count--;
	return (true);
}
