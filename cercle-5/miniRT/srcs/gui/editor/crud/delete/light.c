/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 17:20:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 15:47:29 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "debug.h"

bool	handle_delete_light(t_scene *sc, t_selection *sel, int i)
{
	DBG_INFO_MSG(DBG_CH_EDITOR, "delete_light: type=%d idx=%d\n",
		sel->type, i);
	if (sel->type != TYPE_LIGHT || (size_t)i >= sc->light_count)
	{
		DBG_ERR_MSG(DBG_CH_EDITOR, "delete_light: nothing to delete\n");
		return (false);
	}
	ft_memmove(sc->lights + i, sc->lights + i + 1,
		(sc->light_count - i - 1) * sizeof(t_light));
	sc->light_count--;
	return (true);
}
