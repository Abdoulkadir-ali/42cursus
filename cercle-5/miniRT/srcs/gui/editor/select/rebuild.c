/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rebuild.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 19:10:00 by copilot           #+#    #+#             */
/*   Updated: 2026/03/26 11:20:30 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	rebuild_bvh(t_gui *gui)
{
	if (gui->rt.bvh)
		bvh_destroy(gui->rt.bvh);
	gui->rt.bvh = bvh_build_global(gui->scene);
	gui->scene->version++;
}
